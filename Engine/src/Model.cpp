#include "Model.h"

#include "glad/gl.h"
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>



Model::Model() {
    loadModel();
}

void Model::loadModel() {

    Vertex v1 = { { -0.5f, -0.5f, 0.0f}, { 1.000f, 0.988f, 0.353f}  };
    Vertex v2 = { {  0.5f, -0.5f, 0.0f}, { 0.357f, 0.788f, 0.173f}  };
    Vertex v3 = { {  0.5f,  0.5f, 0.0f}, { 0.067f, 0.357f, 0.941f }  };
    Vertex v4 = { { -0.5f,  0.5f, 0.0f}, { 0.941f, 0.063f, 0.063f }  };

    std::vector<Vertex> vertices = { v1, v2, v3, v4 };

    std::vector<unsigned int> indices = { 0, 1, 2,  2, 3, 0 };

    meshes.emplace_back(vertices, indices);
}



void Model::Draw(Shader& shader)
{
    for (Mesh& mesh : meshes) {
        mesh.Draw(shader);
    }
}

void Model::Translate(glm::vec3 vec)
{
    glm::mat4 setter = glm::mat4(1.0f);
    Matrix = glm::translate(setter, vec);
}