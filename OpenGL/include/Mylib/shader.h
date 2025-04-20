#ifndef MYLIB_SHADER_H
#define MYLIB_SHADER_H
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Shader
{
private:

public:
    unsigned int program;
    Shader(const char* vertexShaderPath, const char* fragmentShaderPath);
    // ~Shader();
    // 启用该shader
    void Use();
    // 设置该shader中uniform的值
    void SetBool(const char *name, bool value);
    void SetInt(const char *name, int value);
    void SetFloat(const char *name, float value);
    void SetVec3(const char *name, float value1, float value2, float value3);
    void SetVec3(const char *name, glm::vec3 vec3);
};

#endif
