#version 440 core

// Output fragment color
out vec4 FragColor;

// Inputs from vertex shader
in vec3 color;
in vec2 texCoord;

// Texture sampler
uniform sampler2D tex0;

void main()
{
    // Sample the texture color at the interpolated texture coordinate
    vec4 texColor = texture(tex0, texCoord);
    FragColor = texColor;

  
    // Combine vertex color and texture color (modulate)
    FragColor = texture(tex0, texCoord);
}
