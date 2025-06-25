#version 330 core
out vec4 FragColor;

in vec3 Color;
in vec3 Pos;

void main()
{
    FragColor = vec4(0.2, 0.1, 0.3, 0.5); // solid black outline
}
