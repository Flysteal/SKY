#pragma once

#include <glad/gl.h>
#include <glm/glm.hpp>
#include <assimp/scene.h>
#include <string>
#include <vector>
#include "Mesh.h"
#include "Shader.h"

class Model {
public:
    Model(const std::string& path);
    void Draw(Shader& shader);
    glm::mat4 Matrix = glm::mat4(1.0f);
    void Translate(glm::vec3 vec);

private:
    std::vector<Mesh> meshes;
    std::string directory;
    std::vector<Texture> textures_loaded;

    void loadModel(const std::string& path);
    void processNode(aiNode* node, const aiScene* scene);
    Mesh processMesh(aiMesh* mesh, const aiScene* scene);
    std::vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName);
    unsigned int TextureFromFile(const char* path, const std::string& directory);
};
