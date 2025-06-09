#version 420 core

layout (location = 0) in vec3 aPos;

uniform mat4 camMatrix;
uniform mat4 model;
out vec3 vColor;

void main()
{
    vec4 worldPos = model * vec4(aPos, 1.0);
    gl_Position = camMatrix * worldPos;
    vColor = (worldPos.xyz + vec3(1.0)) * 0.5;
}