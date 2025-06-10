#version 330 core

in vec2 TexCoords;
in vec3 FragPos;
in vec3 Normal;
in vec3 vertexColor;

out vec4 FragColor;

uniform sampler2D texture_diffuse;
uniform bool useTexture;

void main()
{
    vec3 color = useTexture ? texture(texture_diffuse, TexCoords).rgb : vertexColor;

    vec3 lightDir = normalize(vec3(0.5, 1.0, 0.3));
    float diff = max(dot(normalize(Normal), lightDir), 0.0);

    vec3 finalColor = color * diff;
    FragColor = vec4(finalColor, 1.0);
}
