#version 330 core
layout(location = 0) in vec3 aPos;
layout(location = 3) in vec3 aColor;

uniform mat4 model;
uniform mat4 camMatrix;

out vec3 Pos;
out vec3 Color;

void main()
{
    Pos = aPos;
    Color = aColor;
    gl_Position = camMatrix * model * vec4(aPos, 1.0);
}
