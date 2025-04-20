#include <mylib/shader.h>
#include <glad.h>
#include <fstream>
#include <sstream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

Shader::Shader(const char *vertexShaderPath, const char *fragmentShaderPath)
{ // 编译链接着色器并且删除着色器
    std::string vertexCode;
    std::string fragmentCode;
    std::ifstream vertexShaderFile, fragmentShaderFile;
    try
    {
        // 文件流
        vertexShaderFile.open(vertexShaderPath);
        fragmentShaderFile.open(fragmentShaderPath);
        // 字符串流
        std::stringstream vertexShaderStream, fragmentShaderStream;
        vertexShaderStream << vertexShaderFile.rdbuf(); // 缓冲区内容复制
        fragmentShaderStream << fragmentShaderFile.rdbuf();
        vertexShaderFile.close();
        fragmentShaderFile.close();
        vertexCode = vertexShaderStream.str(); // 操作缓冲区
        fragmentCode = fragmentShaderStream.str();
        // std::cout << vertexCode;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    const char* vShaderCode = vertexCode.c_str();
    const char* fShaderCode = fragmentCode.c_str();
    int success;
    char infoLog[512];
    unsigned int vertex = glCreateShader(GL_VERTEX_SHADER);
    unsigned int fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(vertex, 1, &vShaderCode, NULL);
    glShaderSource(fragment, 1, &fShaderCode, NULL);
    glCompileShader(vertex);
    glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
    if(!success){
        glGetShaderInfoLog(vertex, 512, NULL, infoLog);
        std::cout << "Vertex Compile Failed: " << infoLog << std::endl;
    }
    glCompileShader(fragment);
    glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
    if(!success){
        glGetShaderInfoLog(fragment, 512, NULL, infoLog);
        std::cout << "Fragment Compile Failed: " << infoLog << std::endl;
    }
    program = glCreateProgram();
    glAttachShader(program, vertex);
    glAttachShader(program, fragment);
    glLinkProgram(program);
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(fragment, 512, NULL, infoLog);
        std::cout << "Program Link Failed: " << infoLog << std::endl;
    }
    glDeleteShader(vertex);
    glDeleteShader(fragment);
}

void Shader::Use()
{
    glUseProgram(program);
}

void Shader::SetBool(const char *name, bool value)
{
    glUniform1i(glGetUniformLocation(program, name), (int)value);
}
void Shader::SetInt(const char *name, int value){
    glUniform1i(glGetUniformLocation(program, name), value);
}
void Shader::SetFloat(const char *name, float value){
    glUniform1f(glGetUniformLocation(program, name), value);
}

void Shader::SetVec3(const char *name, float value1, float value2, float value3){
    glUniform3f(glGetUniformLocation(program, name), value1, value2, value3);
}

void Shader::SetVec3(const char *name, glm::vec3 vec3){
    glUniform3f(glGetUniformLocation(program, name), vec3.x, vec3.y, vec3.z);
}
