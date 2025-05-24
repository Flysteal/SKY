#version 330 core

// Positions/Coordinates
layout (location = 0) in vec3 aPos;
// Colors
layout (location = 1) in vec3 aColor;
// Texture Coordinates
layout (location = 2) in vec2 aTex;

// Outputs the color for the Fragment Shader
out vec3 color;
// Outputs the texture coordinates to the fragment shader
out vec2 texCoord;

// Uniform matrices
uniform mat4 model;
uniform mat4 camMatrix;

void main()
{
    // Transform the vertex position from model space to clip space
    gl_Position = camMatrix * model * vec4(aPos, 1.0);

    // Pass data to fragment shader
    color = aColor;
    texCoord = aTex;
}
