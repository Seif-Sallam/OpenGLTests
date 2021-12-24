#pragma once
#include "imgui/imgui.h"
#include "imgui/imgui_impl_opengl3.h"
#include "imgui/imgui_impl_glfw.h"

class OpenGLImGui
{
public:
    static void NewFrame();
    static void EndFrame();
    static void Render();
};