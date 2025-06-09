#version 420 core

// Positions/Coordinates
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec3 aColor;
layout (location = 3) in vec2 aTex;



out vec3 crntPos;
out vec3 Normal;
out vec3 color;
out vec2 TexCoords;



uniform mat4 camMatrix;
uniform mat4 model;


void main()
{

    crntPos = vec3(model * vec4(aPos, 1.0f));
    // Assigns the normal from the Vertex Data to "Normal"
    Normal = aNormal;
    // Assigns the colors from the Vertex Data to "color"
    color = aColor;
    // Assigns the texture coordinates from the Vertex Data to "texCoord"
    TexCoords = aTex;
    
    // Outputs the positions/coordinates of all vertices
    gl_Position = camMatrix * vec4(crntPos, 1.0);
}