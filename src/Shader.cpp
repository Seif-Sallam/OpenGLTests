#include "../headers/Shader.h"
#include <fstream>
#include <sstream>
#include "glm/gtc/type_ptr.hpp"
Shader::Shader(const std::string &fragmentShader, const std::string &vertexShader)
    : m_FragmentShaderName(fragmentShader), m_VertexShaderName(vertexShader)
{
    std::ifstream fragFile, vertexFile;
    std::string vertexCode, fragmentCode;
    fragFile.exceptions(std::ifstream::badbit | std::ifstream::failbit);
    vertexFile.exceptions(std::ifstream::badbit | std::ifstream::failbit);

    try
    {
        fragFile.open(fragmentShader);
        vertexFile.open(vertexShader);

        std::stringstream vertexStream, fragmentStream;
        vertexStream << vertexFile.rdbuf();
        fragmentStream << fragFile.rdbuf();

        vertexCode = vertexStream.str();
        fragmentCode = fragmentStream.str();

        fragFile.close();
        vertexFile.close();
    }
    catch (std::ifstream::failure f)
    {
        std::cout << "ERROR::SHADER::FILE WAS NOT READ CORRECTLY\n";
    }

    unsigned int vertexID, fragmentID;
    vertexID = glCreateShader(GL_VERTEX_SHADER);
    fragmentID = glCreateShader(GL_FRAGMENT_SHADER);
    const char *finalVertexCode = vertexCode.c_str();

    glShaderSource(vertexID, 1, &finalVertexCode, nullptr);
    glCompileShader(vertexID);
    CheckError(vertexID, "SHADER");

    const char *finalFragCode = fragmentCode.c_str();

    glShaderSource(fragmentID, 1, &finalFragCode, nullptr);
    glCompileShader(fragmentID);
    CheckError(fragmentID, "SHADER");

    ID = glCreateProgram();
    glAttachShader(ID, vertexID);
    glAttachShader(ID, fragmentID);
    glLinkProgram(ID);
    CheckError(ID, "PROGRAM");

    glDeleteShader(vertexID);
    glDeleteShader(fragmentID);
}

Shader::~Shader()
{
    glDeleteProgram(ID);
    glUseProgram(0);
}

void Shader::Bind()
{
    glUseProgram(ID);
}

void Shader::UnBind()
{
    glUseProgram(0);
}

void Shader::SetFloat(const std::string &name, float value) const
{
    unsigned int location = GetUniformLocation(name);
    glUniform1f(location, value);
}

void Shader::SetInt(const std::string &name, int value) const
{
    unsigned int location = GetUniformLocation(name);
    glUniform1i(location, value);
}

void Shader::SetBool(const std::string &name, bool value) const
{
    unsigned int location = GetUniformLocation(name);
    glUniform1i(location, int(value));
}

void Shader::SetVec2(const std::string &name, const glm::vec2 &value) const
{
    unsigned int location = GetUniformLocation(name);
    glUniform2fv(location, 1, glm::value_ptr(value));
}

void Shader::SetVec2(const std::string &name, float x, float y) const
{
    unsigned int location = GetUniformLocation(name);
    glUniform2f(location, x, y);
}

void Shader::SetVec3(const std::string &name, const glm::vec3 &value) const
{
    unsigned int location = GetUniformLocation(name);
    glUniform3fv(location, 1, glm::value_ptr(value));
}

void Shader::SetVec3(const std::string &name, float x, float y, float z) const
{
    unsigned int location = GetUniformLocation(name);
    glUniform3f(location, x, y, z);
}

void Shader::SetVec4(const std::string &name, const glm::vec4 &value) const
{
    unsigned int location = GetUniformLocation(name);
    glUniform4fv(location, 1, glm::value_ptr(value));
}

void Shader::SetVec4(const std::string &name, float x, float y, float z, float w) const
{
    unsigned int location = GetUniformLocation(name);
    glUniform4f(location, x, y, z, w);
}

void Shader::SetMat2(const std::string &name, const glm::mat2 &value) const
{
    unsigned int location = GetUniformLocation(name);
    glUniformMatrix2fv(location, 1, GL_FALSE, glm::value_ptr(value));
}

void Shader::SetMat3(const std::string &name, const glm::mat3 &value) const
{
    unsigned int location = GetUniformLocation(name);
    glUniformMatrix3fv(location, 1, GL_FALSE, glm::value_ptr(value));
}

void Shader::SetMat4(const std::string &name, const glm::mat4 &value) const
{
    unsigned int location = GetUniformLocation(name);
    glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(value));
}

void Shader::CheckError(unsigned int id, const std::string &type)
{
    int success;
    char infoLog[1024];
    if (type == "PROGRAM")
    {
        glGetProgramiv(id, GL_LINK_STATUS, &success);
        if (!success)
        {
            glGetProgramInfoLog(id, 1024, nullptr, infoLog);
            std::cout << "ERROR::SHADER::PROGRAM COULDN'T LINK THE PROGRAM: \n";
            std::cout << infoLog << std::endl;
        }
    }
    else if (type == "SHADER")
    {
        glGetShaderiv(id, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(id, 1024, nullptr, infoLog);
            std::cout << "ERROR::SHADER:: COULDN'T COMPILE THE SHADER\n"
                      << infoLog << std::endl;
        }
    }
}

uint32_t Shader::GetUniformLocation(const std::string &name) const
{
    if (m_UniformLocations.find(name) != m_UniformLocations.end())
        return m_UniformLocations.at(name);

    unsigned int location = glGetUniformLocation(ID, name.c_str());
    m_UniformLocations[name] = location;

    return location;
}