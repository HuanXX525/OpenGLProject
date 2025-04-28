#include <component/windows/main/main.h>
#include <component/windows/control/control.h>
#include <component/windows/interface/windows.h>
#include <spdlog/spdlog.h>
namespace deluge_windows
{
    namespace deluge_windows_windows
    {
        float Windows::screenWidth;
        float Windows::screenHeight;
        Windows::Windows(){
            deluge_control::Control control;
            int test = control.Init();
            if (!glfwInit())
            {
                this->returnMain = new int(-1); // 初始化失败
                return;
            }
            this->returnMain = new int(0);
            return;
        }
        Windows::~Windows(){
            
        }
        Windows* Windows::createWindows(char* title)
        {
            if(*(this->returnMain) == -1){
                return this;
            }
            Windows::screenWidth = GetSystemMetrics(SM_CXFULLSCREEN);
            Windows::screenHeight = GetSystemMetrics(SM_CYFULLSCREEN);
            this->width = Windows::screenWidth;
            this->height = Windows::screenHeight;
            
            this->title = title;
            this->glfwWindow = glfwCreateWindow(static_cast<int>(width * 0.9), static_cast<int>(height * 0.9), title, NULL, NULL);
            if (!this->glfwWindow)
            {
                glfwTerminate(); // 窗口创建失败
                this->returnMain = new int(-1);
            }
            this->initGlslVersion();
            this->makeContextCurrent();
            this->initGlad();
            this->initImgui();
            return this;
        }
        Windows* Windows::initGlslVersion(){
            if(*(this->returnMain) == -1){
                return this;
            }
            //版本
            glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
            //核心渲染模式
            glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
            return this;
        }
        Windows* Windows::makeContextCurrent(){
            if(*(this->returnMain) == -1){
                return this;
            }
            // 4. 设置当前上下文
            glfwMakeContextCurrent(this->glfwWindow);
            return this;
        }
        Windows* Windows::redrawWindow(int width,int height)
        {
            if(*(this->returnMain) == -1){
                return this;
            }
            // glViewport(0, 0, width, height);
            return this;
        }
        Windows* Windows::initGlad(){
            if(*(this->returnMain) == -1){
                return this;
            }
            // 5. 初始化 GLAD（如果是用 GLAD 加载 OpenGL）
            if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
            {
                glfwTerminate();
                this->returnMain = new int(-1);
                return this;
            }
            return this;
        }
        Windows* Windows::initImgui(){
            if(*(this->returnMain) == -1){
                return this;
            }
            IMGUI_CHECKVERSION();
            ImGui::CreateContext();
            ImGuiIO &io = ImGui::GetIO();
            (void)io;

            // 设置 ImGui 样式（可选）
            ImGui::StyleColorsDark();

            // 绑定 GLFW 和 OpenGL
            ImGui_ImplGlfw_InitForOpenGL(this->glfwWindow, true);
            ImGui_ImplOpenGL3_Init("#version 330");
            glfwSetWindowUserPointer(this->glfwWindow, this);
            glfwSetFramebufferSizeCallback(this->glfwWindow, deluge_control::framebuffer_size_callback); // 暂时先把回调写在这里
            return this;
        }
        float Windows::imGuiFontScale(){
            return this->width / (1920 / 2); // 根据获得的屏幕尺寸调整缩放比例
        }

    } // namespace deluge_windows_windows
} // namespace deluge_windows

namespace huanxx_windows
{
    namespace huanxx_windows_windows
    {
        // huanxx_windows::huanxx_windows_windows::Window Mainwindow(windowWidth, windowHeight, "My Window"); // 创建窗口
        // const float imGuiFontScale = Mainwindow.screenWidth / (1920 / 2);
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
