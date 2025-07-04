#ifndef VERTEX_H
#define VERTEX_H

#include <glm/glm.hpp>


struct Vertex {
    glm::vec3 Position;
    glm::vec3 Normal;
    glm::vec2 TexCoords;
    glm::vec3 Color;  // add this!
};


#endif // VERTEX_H
