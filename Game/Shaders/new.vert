#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;
layout (location = 3) in vec3 aColor;

uniform mat4 model;
uniform mat4 camMatrix;

out vec2 TexCoords;
out vec3 FragPos;
out vec3 Normal;
out vec3 vertexColor;

void main()
{
    FragPos = vec3(model * vec4(aPos, 1.0));
    Normal = mat3(transpose(inverse(model))) * aNormal;
    TexCoords = aTexCoords;
    vertexColor = aColor; 
    gl_Position = camMatrix * vec4(FragPos, 1.0);
}
