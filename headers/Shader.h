#include <string>
#include <iostream>
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "glm/glm.hpp"
#include <unordered_map>
class Shader
{
public:
    Shader(const std::string &fragmentShader, const std::string &vertexShader);
    ~Shader();
    void Bind();
    void UnBind();

    void SetFloat(const std::string &name, float value) const;
    void SetInt(const std::string &name, int value) const;
    void SetBool(const std::string &name, bool value) const;

    void SetVec2(const std::string &name, const glm::vec2 &value) const;
    void SetVec2(const std::string &name, float x, float y) const;

    void SetVec3(const std::string &name, const glm::vec3 &value) const;
    void SetVec3(const std::string &name, float x, float y, float z) const;

    void SetVec4(const std::string &name, const glm::vec4 &value) const;
    void SetVec4(const std::string &name, float x, float y, float z, float w) const;

    void SetMat2(const std::string &name, const glm::mat2 &value) const;

    void SetMat3(const std::string &name, const glm::mat3 &value) const;

    void SetMat4(const std::string &name, const glm::mat4 &value) const;

    unsigned int ID;

private:
    void CheckError(unsigned int id, const std::string &type);
    uint32_t GetUniformLocation(const std::string &name) const;

    mutable std::unordered_map<std::string, uint32_t> m_UniformLocations;
    std::string m_FragmentShaderName;
    std::string m_VertexShaderName;
};