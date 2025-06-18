#ifndef MODEL_H
#define MODEL_H

#include <glm/glm.hpp>
#include <string>
#include <vector>
#include <unordered_map>

#include "Shader.h"
#include "Mesh.h"
#include "Texture.h"
#include "Material.h"

class Model {
public:
    Model(const std::string& path);
    void Draw(Shader& shader);
    void Translate(glm::vec3 vec);

    glm::mat4 Matrix = glm::mat4(1.0f);

private:
    std::vector<Mesh> meshes;
    Texture diffuseTexture; // error texture

    std::unordered_map<std::string, Material> materials;

    void loadModel(const std::string& path);

    // Helper to load materials from MTL file
    std::unordered_map<std::string, Material> loadMTL(const std::string& mtlPath);


    std::string directory; // directory of model file (for relative texture paths)
};

#endif // MODEL_H
