#include <component/windows/main/main.h>
#include <component/windows/control/control.h>
#include <component/windows/interface/windows.h>
#include <GLFW/glfw3.h>
#include <spdlog/spdlog.h>
namespace deluge_windows
{
    namespace deluge_windows_windows
    {
        Windows::Windows(){
            deluge_control::Control control;
            int test = control.Init();
        }
        Windows::~Windows(){
            
        }
        Windows* Windows::createWindows(char* title)
        {
            this->width = GetSystemMetrics(SM_CXFULLSCREEN);
            this->height = GetSystemMetrics(SM_CYFULLSCREEN);
            this->title = title;
            this->glfwWindow = glfwCreateWindow(static_cast<int>(width * 0.9), static_cast<int>(height * 0.9), title, NULL, NULL);
            return this;
        }
        Windows* Windows::redrawWindow(int width,int height)
        {
            // glViewport(0, 0, width, height);
            return this;
        }
        float Windows::screenWidth = 880.0f;
        float Windows::screenHeight = 660.0f;
    } // namespace deluge_windows_windows
} // namespace deluge_windows

namespace huanxx_windows
{
    namespace huanxx_windows_windows
    {
        Window::Window(int width, int height, const char *windowTitle)
        {
            #ifdef _WIN32
                windowWidth = GetSystemMetrics(SM_CXFULLSCREEN);
                windowHeight = GetSystemMetrics(SM_CYFULLSCREEN);
                screenWidth = windowWidth;
            #endif
            // 1. 初始化 GLFW
            if (!glfwInit())
            {
                spdlog::error("Failed to initialize GLFW!");
                return; // 初始化失败
            }

            // 2. 配置 GLFW（可选）
            glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
            glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

            // 3. 创建窗口
            window = glfwCreateWindow(static_cast<int>(windowWidth * 0.9), static_cast<int>(windowHeight * 0.9), windowTitle, NULL, NULL);
            if (!window)
            {
                spdlog::error("Failed to create GLFW window!");
                glfwTerminate(); // 窗口创建失败
                return;
            }

            // 4. 设置当前上下文
            glfwMakeContextCurrent(window);

            // 5. 初始化 GLAD（如果是用 GLAD 加载 OpenGL）
            if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
            {
                spdlog::error("Failed to initialize GLAD!");
                glfwTerminate();
                return;
            }
            glfwSetWindowUserPointer(window, this);
            glfwSetFramebufferSizeCallback(window, Window::framebuffer_size_callback);
            glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

            IMGUI_CHECKVERSION();
            ImGui::CreateContext();
            ImGuiIO &io = ImGui::GetIO();
            (void)io;

            // 设置 ImGui 样式（可选）
            ImGui::StyleColorsDark();

            // 绑定 GLFW 和 OpenGL
            ImGui_ImplGlfw_InitForOpenGL(window, true);
            ImGui_ImplOpenGL3_Init("#version 330");
            //
            imguiInfo = new ImGuiInfo(io, ImGui::GetStyle());
        }
        Window::~Window()
        {
            delete imguiInfo;
        }
        void Window::framebuffer_size_callback(GLFWwindow *window, int width, int height)
        {
            Window *win = static_cast<Window *>(glfwGetWindowUserPointer(window));
            glViewport(0, 0, width, height);
            win->windowWidth = static_cast<float>(width);
            win->windowHeight = static_cast<float>(height);
        }
        Window::ImGuiInfo::ImGuiInfo(ImGuiIO &io, ImGuiStyle &style) : io(io), style(style) {}
    }
}
