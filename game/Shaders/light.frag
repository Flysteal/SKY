#version 330 core

out vec4 FragColor;

// Inputs the color from the Vertex Shader
in vec3 color;
// Inputs the texture coordinates from the Vertex Shader
in vec2 texCoord;

// Gets the Texture Unit from the main function
uniform sampler2D tex0;

void main()
{
    vec4 texColor = texture(tex0, texCoord);
    // Modulate texture color by the vertex input color
    FragColor = vec4(color, 1.0) * texColor;
}