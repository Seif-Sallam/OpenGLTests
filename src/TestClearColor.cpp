#include "../headers/TestClearColor.h"
#include "glad/glad.h"
#include "GLFW/glfw3.h"

namespace test
{
    TestClearColor::TestClearColor()
        : m_ClearColor{0.63f, 0.46f, 0.86f, 1.0f}
    {
    }

    TestClearColor::~TestClearColor()
    {
    }

    void TestClearColor::OnUpdate(float deltaTime)
    {
    }

    void TestClearColor::OnImGuiRender()
    {
        ImGui::ColorEdit4("Clear Color: ", m_ClearColor);
    }

    void TestClearColor::OnRender()
    {
        glClearColor(m_ClearColor[0], m_ClearColor[1], m_ClearColor[2], m_ClearColor[3]);
        glClear(GL_COLOR_BUFFER_BIT);
    }

}