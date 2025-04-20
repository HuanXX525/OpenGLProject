#include <glad.h>
#include <GLFW/glfw3.h>
#include <Mylib/shader.h>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

int main()
{
    // 1. 初始化 GLFW
    if (!glfwInit())
    {
        return -1; // 初始化失败
    }

    // 2. 配置 GLFW（可选）
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // 3. 创建窗口
    GLFWwindow *window = glfwCreateWindow(800, 600, "My Window", NULL, NULL);
    if (!window)
    {
        glfwTerminate(); // 窗口创建失败
        return -1;
    }

    // 4. 设置当前上下文
    glfwMakeContextCurrent(window);

    // 5. 初始化 GLAD（如果是用 GLAD 加载 OpenGL）
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        glfwTerminate();
        return -1;
    }

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    (void)io;

    // 设置 ImGui 样式（可选）
    ImGui::StyleColorsDark();

    // 绑定 GLFW 和 OpenGL
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330");
    // 三角形
    float vertices[] = {
        -0.5f, -0.5f, 0.0f, // left
        0.5f, -0.5f, 0.0f,  // right
        0.0f, 0.5f, 0.0f    // top
    };

    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);

    // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
    // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
    glBindVertexArray(0);
    Shader shader = Shader("shader/simple.vert", "shader/simple.frag");

    // 6. 主循环
    while (!glfwWindowShouldClose(window))
    { // 检查闪退位置
        glfwPollEvents();


        
        
        // 开始 ImGui 帧
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        
        // 绘制 ImGui 控件
        ImGui::ShowDemoWindow();

        // 清除颜色缓冲和深度缓冲
        glClearColor(0.0f, 0.6f, 0.9f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        shader.Use();
        // draw our first triangle
        glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
        glDrawArrays(GL_TRIANGLES, 0, 3);

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        glfwPollEvents();
        glfwSwapBuffers(window);
    }

    // 7. 清理资源
    glfwTerminate();
    return 0;
}