#include <mylib/init.h>

void Window::framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

Window::InitReturn* Window::Init(const char* windowTitle)
{
    // Init GLFW
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // major version
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); // minor version
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // use core mode
    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, windowTitle, NULL, NULL);
    if (window == NULL) {
        spdlog::error("Init window {} failed!", windowTitle);
        glfwTerminate();
        return NULL;
    }
    glfwMakeContextCurrent(window); // 将窗口上下文切换至当前上下文
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback); // 当帧缓冲区大小变化时，重新调整glViewport的大小
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) { // 初始化GLAD
        spdlog::error("GLAD Init failed!");
        return NULL;
    }
    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable; // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;       // Enable Multi-Viewport / Platform Windows
    //io.ConfigViewportsNoAutoMerge = true;
    //io.ConfigViewportsNoTaskBarIcon = true;
    ImGuiStyle& style = ImGui::GetStyle();
    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        style.WindowRounding = 0.0f;
        style.Colors[ImGuiCol_WindowBg].w = 1.0f;
    }

    // io.Fonts->AddFontFromFileTTF("msyh.ttc", 18.0f, nullptr,
    //     io.Fonts->GetGlyphRangesChineseFull());
    ImGui_ImplGlfw_InitForOpenGL(window, true);      // Second param install_callback=true will install GLFW callbacks and chain to existing ones.
    ImGui_ImplOpenGL3_Init("#version 330 core");

    InitReturn out(window, io, style);

    return &out;
}
