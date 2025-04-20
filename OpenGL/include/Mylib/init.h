#ifndef MYLIB_INIT_H
#define MYLIB_INIT_H
#include <glad.h>
#include <GLFW/glfw3.h>
#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>
#include <imgui/imgui_internal.h>
#include <spdlog/spdlog.h>
// Window config
#define WIDTH 1600
#define HEIGHT 900


namespace Window {
    class InitReturn {
    public:
        GLFWwindow* window;
        ImGuiIO& io;
        ImGuiStyle& style;

        InitReturn(GLFWwindow* window, ImGuiIO& io, ImGuiStyle& style)
            : window(window), io(io), style(style)
        {
        }
    };

    void framebuffer_size_callback(GLFWwindow* window, int width, int height); // 处理窗口大小变化
    InitReturn* Init(const char* windowTitle);
}



#endif
