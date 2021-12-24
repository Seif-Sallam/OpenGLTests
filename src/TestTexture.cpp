#include "../headers/TestTexture.h"
#include "glm/mat4x4.hpp"
#include "glm/gtc/matrix_transform.hpp"
namespace test
{
    TestTexture::TestTexture()
        : m_TranslationA(glm::vec3(200.0f, 200.0f, 0.0f)),
          m_TranslationB(glm::vec3(400.0f, 200.0f, 0.0f))
    {
        m_VAO.Bind();
        m_VBLayout.Push<float>(2);
        m_VBLayout.Push<float>(2);

        float pos[] = {
            -50.0f, -50.0f, 0.0f, 0.0f,
            50.0f, -50.0f, 1.0f, 0.0f,
            50.0f, 50.0f, 1.0f, 1.0f,
            -50.0f, 50.0f, 0.0f, 1.0f};
        GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
        GLCall(glEnable(GL_BLEND));
        unsigned int indicies[] = {
            0, 1, 2,
            2, 3, 0};
        m_VBO = new VertexBuffer(pos, 16 * sizeof(float));

        m_VAO.AddBuffer(*m_VBO, m_VBLayout);
        m_IBO = new IndexBuffer(indicies, 6);
        m_Shader = new Shader("res/shaders/basic.shader");
        m_Shader->Bind();
        m_Shader->SetUniform4f("u_Color", 0.2f, 0.3f, 0.8f, 1.0f);
        m_Texture = new Texture("res/textures/Jerry.png");
        m_Texture->Bind();
        m_Shader->SetUniform1i("u_Texture", 0);

        m_VAO.UnBind();
        m_IBO->UnBind();
        m_VBO->UnBind();
        m_Shader->Unbind();
    }

    TestTexture::~TestTexture()
    {
        delete m_VBO;
        delete m_IBO;
        delete m_Shader;
        delete m_Texture;
    }

    void TestTexture::OnImGuiRender()
    {
        ImGui::SliderFloat3("Translation A", &m_TranslationA.x, 0.0f, 960.0f);
        ImGui::SliderFloat3("Translation B", &m_TranslationB.x, 0.0f, 960.0f);
        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
    }

    void TestTexture::OnRender()
    {
        static float r = 0.05f;
        static float increment = 0.05f;
        if (r > 1.f)
            increment = -0.005f;
        else if (r < 0.f)
            increment = 0.005f;

        r += increment;

        glm::mat4 proj = glm::ortho(0.0f, 960.0f, 0.0f, 540.f, -1.0f, 1.0f);
        glm::mat4 view = glm::translate(glm::mat4(1.f), glm::vec3(0.0f, 0.0f, 0.0f));

        {
            glm::mat4 model = glm::translate(glm::mat4(1.f), m_TranslationA);
            glm::mat4 mvp = proj * view * model;

            m_Texture->Bind();
            m_Shader->Bind();
            m_Shader->SetUniform4f("u_Color", r, 0.3f, 0.8f, 1.0f);
            m_Shader->SetUniformMat4f("u_MVP", mvp);
            Renderer::Draw(m_VAO, *m_IBO, *m_Shader);
        }
        {
            glm::mat4 model = glm::translate(glm::mat4(1.f), m_TranslationB);
            glm::mat4 mvp = proj * view * model;

            m_Texture->Bind();
            m_Shader->Bind();
            m_Shader->SetUniform4f("u_Color", r, 0.3f, 0.8f, 1.0f);
            m_Shader->SetUniformMat4f("u_MVP", mvp);
            Renderer::Draw(m_VAO, *m_IBO, *m_Shader);
        }
    }
}
