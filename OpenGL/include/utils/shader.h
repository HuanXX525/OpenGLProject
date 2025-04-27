#ifndef MYLIB_SHADER_H
#define MYLIB_SHADER_H
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace huanxx_utils{
    /// @brief 着色器类，根据传入的顶点着色器和片段着色器路径编译和链接着色器程序
    /// @note 默认开启深度测试
    class Shader
    {
    private:
        bool enableDeepTest = true; // 是否启用深度测试
    public:
        unsigned int program; // 着色器程序ID

        /// @brief 着色器类构造函数
        /// @param vertexShaderPath 顶点着色器路径
        /// @param fragmentShaderPath 片段着色器路径
        Shader(const char *vertexShaderPath, const char *fragmentShaderPath);

        /// @brief 启用该着色器
        void Use();
        /// @brief 传递布尔值到着色器
        /// @param name 着色器变量名称
        /// @param value 着色器变量值
        void SetBool(const char *name, bool value);
        /// @brief 传递整数值到着色器
        /// @param name 着色器变量名称
        /// @param value 着色器变量值
        void SetInt(const char *name, int value);
        /// @brief 传递浮点数值到着色器
        /// @param name 着色器变量名称
        /// @param value 着色器变量值
        void SetFloat(const char *name, float value);
        /// @brief 传递1x3向量到着色器
        /// @param name 着色器变量名称
        /// @param value1 着色器向量维度一
        /// @param value2 着色器向量维度二
        /// @param value3 着色器向量维度三
        void SetVec3(const char *name, float value1, float value2, float value3);
        /// @brief 传递1x3向量到着色器
        /// @param name 着色器变量名称
        /// @param vec3 着色器向量 glm
        void SetVec3(const char *name, glm::vec3 vec3);
        /// @brief 设置深度测试
        /// @param enableDeepTest 是否开启深度测试
        void SetDeepTest(bool enableDeepTest);
    };
}
#endif
    