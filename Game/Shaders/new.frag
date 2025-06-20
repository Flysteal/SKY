#version 330 core
out vec4 FragColor;

in vec3 Color;
in vec3 Pos;

void main()
{
    FragColor = vec4(Pos, 1.0); // solid black outline
}
