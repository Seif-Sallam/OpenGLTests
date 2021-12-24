#include "../headers/Window.h"
#include <imgui/imgui.h>
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

int32_t Window::m_Height;
int32_t Window::m_Width;

Window::Window(int width, int height, const std::string &title)
    : m_Window(nullptr)
{
    m_Width = width;
    m_Height = height;
    Init();
    m_Window = glfwCreateWindow(m_Width, m_Height, title.c_str(), NULL, NULL);
    if (m_Window == NULL)
    {
        std::clog << "Failed to create the GLFW Window\n";
        glfwTerminate();
        throw;
    }

    glfwMakeContextCurrent(m_Window);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        glfwTerminate();
        throw;
    }
    glfwSetFramebufferSizeCallback(m_Window, FrameBufferSizeCallBack);
    InitImGui();
}

void Window::Init()
{
    int err = glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

void Window::InitImGui()
{
    ImGui::CreateContext();
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(m_Window, true);

    ImGui_ImplOpenGL3_Init("#version 130");
}

bool Window::IsOpen()
{
    return !glfwWindowShouldClose(m_Window);
}

void Window::SwapBuffers()
{
    glfwSwapBuffers(m_Window);
}

void Window::PollEevnts()
{
    glfwPollEvents();
    if (glfwGetKey(m_Window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(m_Window, true);
}

void Window::FrameBufferSizeCallBack(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
    m_Width = width;
    m_Height = height;
}

Window::~Window()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwTerminate();
    m_Window = nullptr;
}
