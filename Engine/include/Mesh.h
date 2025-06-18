#ifndef MESH_H
#define MESH_H

#include <vector>

#include "Shader.h"
#include "Vertex.h"

class Mesh {
public:
	Mesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices);

    void Draw(Shader &shader);

private:
    unsigned int VAO, VBO, EBO;

    std::vector<Vertex>       vertices;
    std::vector<unsigned int> indices;

    void setupMesh();
};

#endif