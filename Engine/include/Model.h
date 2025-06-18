#ifndef MODEL_H
#define MODEL_H


#include <glm/glm.hpp>
// #include <string>

#include "Shader.h"
#include "Mesh.h"

#include "Texture.h"

class Model {
public:
    Model(const std::string& path);
    void Draw(Shader& shader);

    void Translate(glm::vec3 vec);
    glm::mat4 Matrix = glm::mat4(1.0f);

private:

    std::vector<Mesh> meshes;
    
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<Texture> textures;

    Texture diffuseTexture;

    void loadModel(const std::string& path);
};


#endif // MODEL_H