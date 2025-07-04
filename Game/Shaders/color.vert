#version 330 core
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aNormal;
layout(location = 2) in vec2 aTexCoords;
layout(location = 3) in vec3 aColor;

out vec2 TexCoords;
out vec3 Normal;

out vec3 FragPos;
out vec3 Color;

uniform mat4 model;
uniform mat4 camMatrix;

void main()
{
    TexCoords = aTexCoords;
    Normal = mat3(transpose(inverse(model))) * aNormal;
    FragPos = vec3(model * vec4(aPos, 1.0));
    Color = aColor;
    gl_Position = camMatrix * vec4(FragPos, 1.0);
}
