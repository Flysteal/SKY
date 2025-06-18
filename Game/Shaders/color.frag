#version 420 core
out vec4 FragColor;

in vec3 ourColor;
in vec2 TexCoords;

uniform sampler2D texture_diffuse1;

void main()
{
    vec4 result = texture(texture_diffuse1, TexCoords);
    FragColor = result;
}
