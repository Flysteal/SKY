#version 330 core

out vec4 FragColor;

in vec3 ourColor;
in vec2 texCoord;

uniform sampler2D tex0; // JPG
uniform sampler2D tex1; // PNG (with alpha)

void main()
{
    vec4 color1 = texture(tex0, texCoord); // JPG
    vec4 color2 = texture(tex1, texCoord); // PNG with alpha

    // Blend using PNG's alpha as the weight
    vec4 finalColor = mix(color1, color2, color2.a);

    // Optional: also multiply with vertex color
    FragColor = finalColor * vec4(ourColor, 1.0);
}
