#pragma once
#include "Test.h"
#include "Renderer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "Shader.h"
#include "Camera.h"
namespace test
{
    class Test3D : public Test
    {
    public:
        Test3D();
        ~Test3D();
        void OnUpdate(float deltaTime);
        void OnImGuiRender();
        void OnRender();

    private:
        void ProcessInput(float deltaTime);
        static void CursorPosCallBack(GLFWwindow *window, double xpos, double ypos);
        VertexArray m_VAO;
        VertexBuffer *m_VBO;
        VertexBufferLayout m_Layout;
        IndexBuffer *m_IBO;
        Shader *m_Shader;
        glm::vec3 m_Position;

        static Camera *m_Camera;
        static float lastMouseX, lastMouseY;
        static bool firstMouseClick;
    };
}