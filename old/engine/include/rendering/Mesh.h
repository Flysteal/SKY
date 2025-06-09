#ifndef MESH_H
#define MESH_H

#include <vector>
#include "Shader.h"

class Mesh {
public:
    Mesh(const std::vector<float>& vertices);
    void Draw(Shader& shader);
    ~Mesh();

private:
    unsigned int vao, vbo;
    size_t vertexCount;
};

#endif