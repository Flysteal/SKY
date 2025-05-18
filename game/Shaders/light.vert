#version 330 core

// Input vertex attributes
layout (location = 0) in vec3 aPos;    // Position coordinates
layout (location = 1) in vec3 aColor;  // Vertex color
layout (location = 2) in vec2 aTex;    // Texture coordinates

// Outputs to fragment shader
out vec3 color;
out vec2 texCoord;

void main()
{
    // Set the position of the current vertex
    gl_Position = vec4(aPos, 1.0);
    
    // Pass color and texture coordinates to the fragment shader
    color = aColor;
    texCoord = aTex;
}
