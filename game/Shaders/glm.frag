#version 440 core

out vec4 FragColor;

in vec3 FragPos;    // Fragment position in world space (from vertex shader)
in vec3 Normal;     // Normal vector at the fragment (from vertex shader)
in vec2 texCoord;   // Texture coords (from vertex shader)

uniform sampler2D tex0;
uniform vec3 lightColor;
uniform vec3 lightPos;
uniform vec3 objectColor;

void main()
{
    // Ambient light
    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * lightColor;

    // Diffuse light
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;

    // Combine lighting results
    vec3 result = (ambient + diffuse) * objectColor;

    // Sample texture color
    vec4 texColor = texture(tex0, texCoord);

    // Final output: modulate lighting with texture
    FragColor = vec4(result, 1.0) * texColor;
}
