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


namespace utils {
    /// @brief 引用必须初始化，因此在Window中无法获取ImGuiIO &，通过这个结构体返回
    class Window {
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
        GLFWwindow* window = nullptr; // 窗口指针
        float windowWidth = 800.0f; // 窗口宽度
        float windowHeight = 600.0f; // 窗口高度
        float screenWidth = 0.0f; // 窗口宽度缩放比例
        /// @brief 最外层窗口的初始化
        /// @param width 窗口宽度
        /// @param height 窗口高度
        /// @param windowTitle 窗口标题
        ImGuiInfo* imguiInfo; // ImGui信息
        Window(int width, int height, const char *windowTitle);
        ~Window();
    };
}



#endif
