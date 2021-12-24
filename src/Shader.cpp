#include "../headers/Shader.h"

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "../headers/Renderer.h"

Shader::Shader(const std::string &filePath)
    : m_FilePath(filePath), m_RendererID(0)
{
    ShaderProgramSource source = ParseShader(filePath);
    m_RendererID = CreateShader(source.VertexSource, source.FragmnetSource);
}

Shader::~Shader()
{
    GLCall(glDeleteProgram(m_RendererID));
}

void Shader::Bind() const
{
    GLCall(glUseProgram(m_RendererID));
}

void Shader::Unbind() const
{
    GLCall(glUseProgram(0));
}

void Shader::SetUniform4f(const std::string &name, float v0, float v1, float v2, float v3)
{
    GLCall(glUniform4f(GetUniformLocation(name), v0, v1, v2, v3));
}

void Shader::SetUniform4fv(const std::string &name, float arr[])
{
    GLCall(glUniform4fv(GetUniformLocation(name), 1, arr));
}

void Shader::SetUniform1f(const std::string &name, float v)
{
    GLCall(glUniform1f(GetUniformLocation(name), v));
}

void Shader::SetUniform1i(const std::string &name, int v)
{
    GLCall(glUniform1i(GetUniformLocation(name), v));
}

void Shader::SetUniformMat4f(const std::string &name, const glm::mat4 &mat)
{
    GLCall(glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, &mat[0][0]));
}

int Shader::GetUniformLocation(const std::string &name)
{
    if (m_UniformLocationCache.find(name) != m_UniformLocationCache.end())
        return m_UniformLocationCache[name];
    std::cout << "Finding the location of uniform " << name << std::endl;
    GLCall(int location = glGetUniformLocation(m_RendererID, name.c_str()));
    if (location == -1)
        std::cout << "Warning: uniform " << name << " doesn't exist!\n";

    m_UniformLocationCache[name] = location;
    return location;
}

unsigned int Shader::CreateShader(const std::string &vertexShader, const std::string &fragmentShader)
{
    unsigned int program = glCreateProgram();
    unsigned int vs = CompileShaders(GL_VERTEX_SHADER, vertexShader);
    unsigned int fs = CompileShaders(GL_FRAGMENT_SHADER, fragmentShader);

    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    glValidateProgram(program);

    glDeleteShader(vs);
    glDeleteShader(fs);
    return program;
}

unsigned int Shader::CompileShaders(unsigned int type, const std::string &source)
{
    GLCall(unsigned int id = glCreateShader(type));
    const char *src = source.c_str();
    GLCall(glShaderSource(id, 1, &src, nullptr));
    GLCall(glCompileShader(id));

    int result;
    GLCall(glGetShaderiv(id, GL_COMPILE_STATUS, &result));
    if (result == GL_FALSE)
    {

        int length;
        GLCall(glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length));
        char *message = (char *)alloca(length * sizeof(char));
        GLCall(glGetShaderInfoLog(id, length, &length, message));
        std::cout << "Failed to Compile " << ((type == GL_VERTEX_SHADER) ? "Vertex" : "Fragment") << " Shader" << std::endl;
        std::cout << message << std::endl;
        GLCall(glDeleteShader(id));
        return 0;
    }

    return id;
}

ShaderProgramSource Shader::ParseShader(const std::string &filepath)
{
    std::ifstream stream(filepath);
    enum class ShaderType
    {
        NONE = -1,
        VERTEX = 0,
        FRAGMENT = 1
    };
    std::string line;
    std::stringstream buf[2];
    ShaderType type = ShaderType::NONE;
    while (getline(stream, line, '\n'))
    {
        if (line.find("#Shader") != std::string::npos)
        {
            if (line.find("Vertex") != std::string::npos)
                type = ShaderType::VERTEX;
            else if (line.find("Fragment") != std::string::npos)
                type = ShaderType::FRAGMENT;
        }
        else
        {
            buf[(int)type] << line << '\n';
        }
    }

    return {buf[0].str(), buf[1].str()};
}
