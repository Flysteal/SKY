#version 330 core

in vec2 TexCoords;
in vec3 FragPos;
in vec3 Normal;

out vec4 FragColor;

uniform sampler2D texture_diffuse;

void main()
{
    vec3 color = texture(texture_diffuse, TexCoords).rgb;

    // Basic diffuse lighting
    vec3 lightDir = normalize(vec3(0.5, 1.0, 0.3));
    float diff = max(dot(normalize(Normal), lightDir), 0.0);

    vec3 finalColor = color * diff;
    FragColor = vec4(finalColor, 1.0);
}
