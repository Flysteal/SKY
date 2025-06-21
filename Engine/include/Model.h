#ifndef MODEL_H
#define MODEL_H

#include <glm/glm.hpp>
#include <string>
#include <vector>
#include <unordered_map>
#include <memory> // <-- Required for shared_ptr

#include "Shader.h"
#include "Mesh.h"
#include "Texture.h"
#include "Material.h"

class Model {
public:
    Model(const std::string& path);
    void Draw(Shader& shader);
    void SetTransform(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale);

    glm::mat4 Matrix = glm::mat4(1.0f);

private:
    std::vector<Mesh> meshes;

    // fallback texture in case MTL is missing
    std::shared_ptr<Texture> fallbackTexture;

    std::unordered_map<std::string, Material> materials;
    std::string directory;

    void loadModel(const std::string& path);
    std::unordered_map<std::string, Material> loadMTL(const std::string& mtlPath);
};

#endif // MODEL_H
