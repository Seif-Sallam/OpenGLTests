#include "../headers/Keyboard.h"
#include "../headers/Window.h"

bool Keyboard::IsKeyPressed(int key)
{
    return glfwGetKey(Window::GetWindow(), key) == GLFW_PRESS;
}
