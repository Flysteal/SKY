#ifndef MESH_H
#define MESH_H

#include <vector>

#include "Shader.h"
#include "Vertex.h"
#include "Texture.h"

class Mesh {
public:
    // Take Texture as rvalue reference to move it
    Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, Texture&& texture);

    void Draw(Shader &shader);

private:
    void setupMesh();
    unsigned int VAO, VBO, EBO;
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    Texture texture;
};

#endif
