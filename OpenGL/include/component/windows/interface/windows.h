#pragma once
#include <component/windows/main/main.h>
#include <component/windows/control/control.h>
#include <glad.h>
#include <GLFW/glfw3.h>
#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>
#include <imgui/imgui_internal.h>
#include <spdlog/spdlog.h>
#ifndef DELUGE_WINDOWS
#define DELUGE_WINDOWS
namespace deluge_windows
{
    namespace deluge_windows_windows
    {
        class Windows
        {
        private:
            /* data */
            char* title;
            Windows* initGlslVersion();
            Windows* makeContextCurrent();
        public:
            int width;
            int height;
            static float screenWidth;
            static float screenHeight;
            GLFWwindow* glfwWindow;
            int* returnMain;
            Windows(/* args */);
            ~Windows();
            Windows* createWindows(char* title);
            Windows* redrawWindow(int width,int height);
            Windows* initGlad();
            Windows* initImgui();
            float imGuiFontScale();
        };
    } // namespace deluge_windows_windows
} // namespace deluge_windows

namespace huanxx_windows
{
    namespace huanxx_windows_windows
    {
        class Window
        {
        private:
            class ImGuiInfo
            {
            public:
                ImGuiIO &io;       // ImGui IO对象
                ImGuiStyle &style; // ImGui样式对象
                ImGuiInfo(ImGuiIO &io, ImGuiStyle &style);
            };
            /// @brief 窗口大小变化时的回调函数
            /// @param window glfw窗口指针
            /// @param width 窗口宽度
            /// @param height 窗口高度
            /// @note 该函数会在窗口大小变化时被调用，重新设置视口大小
            static void framebuffer_size_callback(GLFWwindow *window, int width, int height);

        public:
            GLFWwindow *window = nullptr; // 窗口指针
            float windowWidth = 800.0f;   // 窗口宽度
            float windowHeight = 600.0f;  // 窗口高度
            float screenWidth = 0.0f;     // 窗口宽度缩放比例
            /// @brief 最外层窗口的初始化
            /// @param width 窗口宽度
            /// @param height 窗口高度
            /// @param windowTitle 窗口标题
            ImGuiInfo *imguiInfo; // ImGui信息
            Window(int width, int height, const char *windowTitle);
            ~Window();
        };
    } // namespace deluge_windows_windows
} // namespace huanxx_windows

#endif