#include "../headers/Test3D.h"
#include "../headers/Keyboard.h"
#include "../headers/Window.h"
namespace test
{

    float Test3D::lastMouseX = 0.f;
    float Test3D::lastMouseY = 0.f;
    bool Test3D::firstMouseClick = true;
    Camera *Test3D::m_Camera = nullptr;
    Test3D::Test3D()
    {

        glEnable(GL_DEPTH_TEST);
        m_VAO.Bind();
        m_Layout.Push<float>(3); // positions
        GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
        GLCall(glEnable(GL_BLEND));
        float data[] = {
            // front
            -50.0f, -50.0f, 50.0f,
            50.0f, -50.0f, 50.0f,
            50.0f, 50.0f, 50.0f,
            -50.0f, 50.0f, 50.0f,
            // back
            -50.0f, -50.0f, -50.0f,
            50.0f, -50.0f, -50.0f,
            50.0f, 50.0f, -50.0f,
            -50.0f, 50.0f, -50.0f};
        m_VBO = new VertexBuffer(data, sizeof(data));
        m_VAO.AddBuffer(*m_VBO, m_Layout);
        unsigned int indicies[] = {
            0, 1, 2,
            2, 3, 0,
            // right
            1, 5, 6,
            6, 2, 1,
            // back
            7, 6, 5,
            5, 4, 7,
            // left
            4, 0, 3,
            3, 7, 4,
            // bottom
            4, 5, 1,
            1, 0, 4,
            // top
            3, 2, 6,
            6, 7, 3};
        m_IBO = new IndexBuffer(indicies, sizeof(indicies) / sizeof(unsigned int));

        m_Shader = new Shader("res/shaders/3D.glsl");
        m_Shader->Bind();
        m_Camera = new Camera;
        glfwSetCursorPosCallback(Window::GetWindow(), CursorPosCallBack);
    }

    Test3D::~Test3D()
    {
        delete m_VBO;
        delete m_IBO;
        delete m_Shader;
        delete m_Camera;
    }

    void Test3D::OnUpdate(float deltaTime)
    {
        ProcessInput(deltaTime);
    }

    void Test3D::OnImGuiRender()
    {
        ImGui::SliderFloat3("Position: ", &m_Position.x, 0.0f, 960.0f);
    }

    void Test3D::OnRender()
    {
        glm::mat4 proj = glm::ortho(0.0f, 960.0f, 0.0f, 540.f, -1.0f, 1.0f);
        glm::mat4 view = m_Camera->GetViewMatrix();
        glm::mat4 model = glm::translate(glm::mat4(1.f), m_Position);
        glm::mat4 mvp = proj * view * model;
        m_Shader->Bind();
        m_Shader->SetUniformMat4f("u_MVP", mvp);
        Renderer::Draw(m_VAO, *m_IBO, *m_Shader);
    }

    void Test3D::ProcessInput(float deltaTime)
    {
        if (Keyboard::IsKeyPressed(GLFW_KEY_W))
        {
            m_Camera->ProcessKeyboard(CameraMovement::FORWARD, deltaTime);
        }
        if (Keyboard::IsKeyPressed(GLFW_KEY_S))
        {
            m_Camera->ProcessKeyboard(CameraMovement::BACKWARD, deltaTime);
        }
        if (Keyboard::IsKeyPressed(GLFW_KEY_D))
        {
            m_Camera->ProcessKeyboard(CameraMovement::RIGHT, deltaTime);
        }
        if (Keyboard::IsKeyPressed(GLFW_KEY_A))
        {
            m_Camera->ProcessKeyboard(CameraMovement::LEFT, deltaTime);
        }
    }
    void Test3D::CursorPosCallBack(GLFWwindow *window, double xpos, double ypos)
    {
        if (firstMouseClick)
        {
            lastMouseX = xpos;
            lastMouseY = ypos;
            firstMouseClick = false;
        }
        float xOffset = xpos - lastMouseX;
        float yOffset = xpos - lastMouseY;

        m_Camera->ProcessMouseMovement(xOffset, yOffset);
    }
}