#version 330 core

in vec2 TexCoords;
out vec4 FragColor;

uniform sampler2D diffuseTexture;
uniform float near = 0.1;
uniform float far = 100.0;


void main()
{
    vec4 texColor = texture(diffuseTexture, TexCoords);
    FragColor = texColor;
}

// void main()
// {
//     float z = gl_FragCoord.z * 2.0 - 1.0;
//     float linearDepth = (2.0 * near * far) / (far + near - z * (far - near));
//     float brightness = 1.0 - (linearDepth - near) / (far - near + 1.0);

//     vec4 texColor = texture(diffuseTexture, TexCoords);
//     if(texColor.a < 0.1)
//         discard; // optional: skip almost transparent fragments

//     vec3 fogColor = vec3(0.58, 0.855, 0.902); // light blue fog
//     vec3 color = mix(fogColor, texColor.rgb, brightness); // blend toward blue
//     FragColor = vec4(color, texColor.a);
// }
