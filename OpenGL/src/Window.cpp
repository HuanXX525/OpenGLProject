#include <glad.h>
#include <GLFW/glfw3.h>
#include <utils/shader.h>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <stb_image.h>
#include <spdlog/spdlog.h>
#include <component/windows/interface/windows.h>


const float windowWidth = 800.0f;
const float windowHeight = 600.0f;
int main()
{
    
    huanxx_windows::huanxx_windows_windows::Window Mainwindow(windowWidth, windowHeight, "My Window"); // 创建窗口
    const float imGuiFontScale = Mainwindow.screenWidth / (1920 / 2);
    // 正方形
    float vertices[] = {
        //     ---- 位置 ----       ---- 颜色 ----     - 纹理坐标 -
        0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,   // 右上
        0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,  // 右下
        -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, // 左下
        -0.5f, 0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f   // 左上
    };
    unsigned int indices[] = {
        0, 1, 3, // 第一个三角形
        1, 2, 3  // 第二个三角形
    };
    unsigned int VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    // 纹理
    unsigned int texture;
    glGenTextures(1, &texture);
    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true);
    unsigned char *data = stbi_load("../../../Resource/Unity.png", &width, &height, &nrChannels, 0);
    if (!data)
    {
        spdlog::error("Failed to load texture!");
    }
    glBindTexture(GL_TEXTURE_2D, texture);{
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    }
    stbi_image_free(data);
    // VAO 绑定
    glBindVertexArray(VAO);{
        glBindBuffer(GL_ARRAY_BUFFER, VBO);{
            glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
        }
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);{
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
        }
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)0);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(3 * sizeof(float)));
        glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(6 * sizeof(float)));
        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);
        glEnableVertexAttribArray(2);
    }
    // 解绑
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    // 着色器加载
    huanxx_utils::Shader shader("shader/vertexShader/main.vert", "shader/fragmentShader/main.frag");
    // Imgui 变量
    float Position[3] = {0.0f, 0.0f, 0.0f};
    float Rotation[3] = {0.0f, 0.0f, 0.0f};
    float Scale[3] = {1.0f, 1.0f, 1.0f};
    // 6. 主循环
    while (!glfwWindowShouldClose(Mainwindow.window)){
        glfwPollEvents();

        // 开始 ImGui 帧
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        
        // 1. 绘制 ImGui 控件
        ImGuiWindowFlags window_flags = 0;
        window_flags |= ImGuiWindowFlags_NoCollapse;
        if (ImGui::Begin("My Window", NULL, window_flags))
        {
            ImGui::SetWindowFontScale(imGuiFontScale);
            ImGui::SeparatorText("Transform");
            ImGui::DragFloat3("Position", Position, 0.01f, -1e10, 1e10, "%.2f");
            ImGui::DragFloat3("Rotation", Rotation, 0.1f, -1e10, 1e10, "%.2f");
            ImGui::DragFloat3("Scale", Scale, 0.01f, -1e10, 1e10, "%.2f");
        }
        ImGui::End();

        // 清除颜色缓冲和深度缓冲
        glClearColor(0.0f, 0.6f, 0.9f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        shader.Use();
        // 设置变换矩阵
        glm::mat4 model(1.0f); // 模型到世界坐标系的变换矩阵
        glm::mat4 view(1.0f);  // 世界坐标系到观察坐标系的变换矩阵
        // 确立一个视锥体的基本信息
        model = glm::translate(model, glm::vec3(Position[0], Position[1], Position[2]));
        model = glm::rotate(model, glm::radians(Rotation[0]), glm::vec3(1.0f, 0.0f, 0.0f));
        model = glm::rotate(model, glm::radians(Rotation[1]), glm::vec3(0.0f, 1.0f, 0.0f));
        model = glm::rotate(model, glm::radians(Rotation[2]), glm::vec3(0.0f, 0.0f, 1.0f));
        model = glm::scale(model, glm::vec3(Scale[0], Scale[1], Scale[2]));
        // 设置投影矩阵
        view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f)); // 观察矩阵
        glm::mat4 projection = glm::perspective(glm::radians(45.0f), Mainwindow.windowWidth/Mainwindow.windowHeight, 1.0f, 100.0f);
        // 传递矩阵到着色器
        unsigned int modelLOC = glGetUniformLocation(shader.program, "model");
        unsigned int viewLOC = glGetUniformLocation(shader.program, "view");
        unsigned int projectionLOC = glGetUniformLocation(shader.program, "projection");
        glUniformMatrix4fv(modelLOC, 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(viewLOC, 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(projectionLOC, 1, GL_FALSE, glm::value_ptr(projection));
        // 绑定VAO和纹理
        glBindVertexArray(VAO); 
        glActiveTexture(GL_TEXTURE0); // 激活纹理单元0
        glBindTexture(GL_TEXTURE_2D, texture);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        // 不用管的代码
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        glfwPollEvents();
        glfwSwapBuffers(Mainwindow.window);
    }

    // 7. 清理资源
    glfwTerminate();
    // window = nullptr;
    return 0;
}

