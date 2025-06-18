#version 330 core

in vec2 TexCoords;
out vec4 FragColor;

uniform sampler2D diffuseTexture;
uniform float near = 0.1;
uniform float far = 100.0;

void main()
{
    float z = gl_FragCoord.z * 2.0 - 1.0;
    float linearDepth = (2.0 * near * far) / (far + near - z * (far - near));
    float brightness = 1.0 - (linearDepth - near) / (far - near + 1.0);

    vec3 color = texture(diffuseTexture, TexCoords).rgb;
    color = mix(vec3(1.0), color, brightness); // Fade to white
    FragColor = vec4(color, 1.0);
}