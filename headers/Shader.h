#pragma once
#include <string>
#include <unordered_map>
#include "glm/glm.hpp"

struct ShaderProgramSource {
	std::string VertexSource;
	std::string FragmnetSource;
};
class Shader
{
public:
	Shader(const std::string& filename);
	~Shader();

	void Bind() const;
	void Unbind() const;

	//Set Uniform
	void SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3);
	void SetUniform1f(const std::string& name, float v);
	void SetUniform1i(const std::string& name, int v);
	void SetUniformMat4f(const std::string& name, const glm::mat4& mat);

private:
	int GetUniformLocation(const std::string& name);
	unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader);
	unsigned int CompileShaders(unsigned int type, const std::string& source);
	ShaderProgramSource ParseShader(const std::string& filepath);
	
	
private:
	std::string m_FilePath;
	unsigned int m_RendererID;
	// caching for uniform
	std::unordered_map<std::string, int> m_UniformLocationCache;
};

