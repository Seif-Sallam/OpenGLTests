#pragma once
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "glm/glm.hpp"
#include "Renderer.h"

#include <iostream>
#include <string>
#include "Vec.h"

class Window
{
public:
    Window(int width, int height, const std::string &title, bool fullscreen = false);
    Window(Vec2i resolution, const std::string &title, bool fullscreen = false);
    static GLFWwindow *GetWindow();
    bool IsOpen();
    void SwapBuffers();
    void PollEevnts();
    ~Window();

private:
    static void FrameBufferSizeCallBack(GLFWwindow *window, int width, int height);
    void Init();
    void InitImGui();
    static GLFWwindow *m_Window;
    static int32_t m_Width, m_Height;
};