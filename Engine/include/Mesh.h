#ifndef MESH_H
#define MESH_H

#include <vector>
#include <memory>

#include "Shader.h"
#include "Vertex.h"
#include "Texture.h"

class Mesh {
public:
    // Updated constructor to take shared_ptr<Texture>
    Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::shared_ptr<Texture> texture);

    void Draw(Shader& shader);

private:
    void setupMesh();
    
    unsigned int VAO, VBO, EBO;
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;

    // Shared texture pointer
    std::shared_ptr<Texture> texture;
};

#endif
