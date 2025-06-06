#version 420 core

struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
};

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoord;

out vec4 FragColor;

uniform vec3 lightPos;
uniform vec3 viewPos;

uniform sampler2D tex0;
uniform Material material;

void main()
{
    // Ambient lighting
    vec3 ambient = material.ambient * texture(tex0, TexCoord).rgb;

    // Diffuse lighting
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = material.diffuse * diff * texture(tex0, TexCoord).rgb;

    // Specular lighting
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = material.specular * spec;

    vec3 result = ambient + diffuse + specular;
    FragColor = vec4(result, 1.0);
}
