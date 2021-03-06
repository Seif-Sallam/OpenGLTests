#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <imgui/imgui.h>
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"
#include "../headers/TestClearColor.h"
#include "../headers/TestTexture.h"
#include "../headers/TestInstantiation.h"
#include "../headers/Test3D.h"

#include "../headers/Window.h"
#include "../headers/OpenGLImGui.h"

#include "../headers/Renderer.h"
#include "../headers/VertexArray.h"
#include "../headers/VertexBuffer.h"
#include "../headers/VertexBufferLayout.h"
#include "../headers/IndexBuffer.h"
#include "../headers/Texture.h"

int main()
{
    Window window(800, 600, "LearnOpengl", false);

    test::Test *currentTest = nullptr;
    test::TestMenu testMenu(currentTest);
    currentTest = &testMenu;
    testMenu.RegisterTest<test::TestClearColor>("Clear Color");
    testMenu.RegisterTest<test::TestTexture>("Texture Test");
    testMenu.RegisterTest<test::TestInstantiation>("Test Instantiation");
    testMenu.RegisterTest<test::Test3D>("Test 3D");

    float lastFrame = 0.f;
    float currentFrame = 0.f;
    while (window.IsOpen())
    {
        currentFrame = glfwGetTime();
        float deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        if (currentTest != nullptr)
        {
            currentTest->OnUpdate(deltaTime);
            currentTest->OnRender();
            OpenGLImGui::NewFrame();
            ImGui::Begin("Test Window");
            if (currentTest != &testMenu && ImGui::Button("<-"))
            {
                delete currentTest;
                currentTest = &testMenu;
            }
            currentTest->OnImGuiRender();
            ImGui::End();
            OpenGLImGui::EndFrame();
        }
        OpenGLImGui::Render();

        window.SwapBuffers();
        window.PollEevnts();
    }

    return 0;
}
