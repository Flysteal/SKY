#version 440 core
uniform vec4 lightColor;
out vec4 FragColor;

void main()
{
    FragColor = vec4(lightColor);
}