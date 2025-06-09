#ifndef MESH_H
#define MESH_H

#include <vector>
#include "Shader.h"
#include "glm/vec3.hpp"

class Mesh {
public:
    Mesh(const std::vector<float>& vertices);
    void Draw(Shader& shader);
    ~Mesh();

    glm::vec3 Position = glm::vec3(1.0f);
    glm::vec3 Scale = glm::vec3(1.0f);


private:
    unsigned int vao, vbo;
    size_t vertexCount;
};

#endif // MESH_H