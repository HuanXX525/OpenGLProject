#version 330 core
out vec4 FragColor;
in vec3 vertexColor;
in vec2 TexCoord;

uniform sampler2D ourTexture;

void main()
{
    // FragColor = vec4(1.0f, 1.0f, 1.0f, 1.0f);
    FragColor = texture(ourTexture, TexCoord);
} 