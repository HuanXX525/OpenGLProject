#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexCoord;

out vec3 vertexColor; // 传递给片段着色器的颜色
out vec2 TexCoord;

uniform mat4 model; // 局部坐标系到世界坐标系的变换矩阵
uniform mat4 view; // 世界坐标系到观察坐标系的变换矩阵
uniform mat4 projection; // 观察坐标系到裁剪坐标系的变换矩阵

void main()
{
    gl_Position = projection*view*model*vec4(aPos, 1.0);
    vertexColor = aColor; // 将顶点颜色传递给片段着色器
    TexCoord = aTexCoord;
}