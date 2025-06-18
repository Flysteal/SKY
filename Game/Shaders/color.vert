#version 420 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;

uniform mat4 model;
uniform mat4 camMatrix;
out vec2 TexCoords;

out vec3 ourColor;

void main()
{

    TexCoords = aTexCoords;
    gl_Position =  camMatrix * model * vec4(aPos, 1.0);
}