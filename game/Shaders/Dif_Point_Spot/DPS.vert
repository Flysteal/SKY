#version 440 core

// shader.setVec3("light.direction", -0.2f, -1.0f, -0.3f);//dif


layout(location = 0) in vec3 aPos;       
layout(location = 1) in vec3 aNormal;    
layout(location = 2) in vec2 aTexCoords;

out vec3 FragPos;
out vec3 Normal;
out vec2 TexCoords;

uniform mat4 model;
uniform mat4 camMatrix;

void main()
{
    FragPos = vec3(model * vec4(aPos, 1.0));
    Normal = mat3(transpose(inverse(model))) * aNormal;
    TexCoords = aTexCoords;

    gl_Position = camMatrix * vec4(FragPos, 1.0);
}
