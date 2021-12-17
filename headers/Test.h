#pragma once
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"
#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <array>
#include <functional>

namespace test
{
    class Test
    {
    public:
        Test() {}
        virtual ~Test() {}
        virtual void OnUpdate(float deltaTime) {}
        virtual void OnImGuiRender() {}
        virtual void OnRender() {}
    };

    class TestMenu : public Test
    {
    public:
        TestMenu(Test *&currentTest);
        void OnImGuiRender();
        template <typename T>
        void RegisterTest(const std::string &name)
        {
            m_Tests.push_back(std::make_pair(name, []()
                                             { return new T(); }));
        }

    private:
        std::vector<std::pair<std::string, std::function<Test *()>>> m_Tests;
        Test *&m_CurrentTest;
    };
} // namespace test
