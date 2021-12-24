#include "../headers/TestInstantiation.h"

namespace test
{
    TestInstantiation::TestInstantiation()
    {
        m_VAO.Bind();
        m_Layout.Push<float>(2); // positions
        m_Layout.Push<float>(2); // Texture Coord
        GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
        GLCall(glEnable(GL_BLEND));
        float data[] = {
            -50.0f, -50.0f, 0.0f, 0.0f,
            50.0f, -50.0f, 1.0f, 0.0f,
            50.0f, 50.0f, 1.0f, 1.0f,
            -50.0f, 50.0f, 0.0f, 1.0f};
        m_VBO = new VertexBuffer(data, 16 * sizeof(float));
        m_VAO.AddBuffer(*m_VBO, m_Layout);
        unsigned int indicies[] = {
            0, 1, 2,
            2, 3, 0};
        m_IBO = new IndexBuffer(indicies, 6);

        m_Shader = new Shader("res/shaders/basic.shader");
        m_Shader->Bind();
    }

    TestInstantiation::~TestInstantiation()
    {
        delete m_VBO;
        delete m_IBO;
        delete m_Shader;
    }

    void TestInstantiation::OnUpdate(float deltaTime)
    {
    }

    void TestInstantiation::OnImGuiRender()
    {
        static glm::vec3 positions;
        static float colors[4];
        ImGui::TextUnformatted("Entity Position: ");
        ImGui::SameLine();

        ImGui::SliderFloat3("", &positions[0], 0.f, 600.0f);

        ImGui::TextUnformatted("Color: ");
        ImGui::ColorEdit4("", colors);

        if (ImGui::Button("Add Entity"))
        {
            AddEntity(positions, glm::vec4(colors[0], colors[1], colors[2], colors[3]));
        }
        ImGui::Begin("Entities Number");
        {
            ImGui::Text("The number of entities drawn: %d", int(m_Transformations.size()));
            ImGui::Text("Framerate: %0.3f", ImGui::GetIO().Framerate);
        }

        for (int i = 0; i < m_Transformations.size(); i++)
        {
            ImGui::Text("Entity: %d", i);
            ImGui::SameLine();
            std::string id = "###" + std::to_string(i);
            std::string id2 = "1###" + std::to_string(i);
            ImGui::SliderFloat3(id.c_str(), &m_Transformations[i][0], 0, 600.0f);
            ImGui::ColorEdit4(id2.c_str(), &m_Colors[i][0]);
        }
        ImGui::End();
    }

    void TestInstantiation::OnRender()
    {
        glm::mat4 proj = glm::ortho(0.0f, 960.0f, 0.0f, 540.f, -1.0f, 1.0f);
        glm::mat4 view = glm::translate(glm::mat4(1.f), glm::vec3(0.0f, 0.0f, 0.0f));
        for (int i = 0; i < m_Transformations.size(); i++)
        {
            glm::mat4 model = glm::translate(glm::mat4(1.f), m_Transformations[i]);
            glm::mat4 mvp = proj * view * model;
            m_Shader->Bind();
            // std::cout << m_Colors[i].r << "\n";

            m_Shader->SetUniform4fv("u_Color", &m_Colors[i][0]);
            m_Shader->SetUniformMat4f("u_MVP", mvp);
            Renderer renderer;
            renderer.Draw(m_VAO, *m_IBO, *m_Shader);
        }
    }

    void TestInstantiation::AddEntity(const glm::vec3 &transformation, const glm::vec4 &color)
    {
        m_Transformations.push_back(transformation);
        m_Colors.push_back(color);
    }
}
