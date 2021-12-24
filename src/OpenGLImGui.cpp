#include "../headers/OpenGLImGui.h"

void OpenGLImGui::NewFrame()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}

void OpenGLImGui::EndFrame()
{
    ImGui::EndFrame();
}

void OpenGLImGui::Render()
{
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}
