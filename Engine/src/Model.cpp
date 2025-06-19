#include "Model.h"
#include "Material.h"

#include "glad/gl.h"
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>

#include <fstream>
#include <sstream>
#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>


Model::Model(const std::string& path)
    : diffuseTexture("../../SKY/Game/RSC/brick.jpg") // fallback texture
{
    size_t lastSlash = path.find_last_of("/\\");
    directory = (lastSlash == std::string::npos) ? "" : path.substr(0, lastSlash);
    loadModel(path);
}

void Model::Draw(Shader& shader)
{
    for (Mesh& mesh : meshes)
        mesh.Draw(shader);
}


void Model::Translate(glm::vec3 pos)
{
    Matrix = glm::mat4(1.0f);
    Matrix = glm::translate(Matrix, pos);
}


std::unordered_map<std::string, Material> Model::loadMTL(const std::string& path) {
    std::unordered_map<std::string, Material> materials;
    std::ifstream file(path);
    if (!file.is_open()) {
        std::cerr << "Failed to open MTL file: " << path << "\n";
        return materials;
    }

    std::string line;
    std::string currentMaterialName;

    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string prefix;
        iss >> prefix;

        if (prefix == "newmtl") {
            iss >> currentMaterialName;
            materials[currentMaterialName] = Material();
        }
        else if (prefix == "Kd") {
            float r, g, b;
            iss >> r >> g >> b;
            if (!currentMaterialName.empty()) {
                materials[currentMaterialName].diffuseColor = glm::vec3(r, g, b);
            }
        }
        else if (prefix == "map_Kd") {
            std::string texturePath;
            iss >> texturePath;
            if (!currentMaterialName.empty()) {
                materials[currentMaterialName].diffuseTexPath = texturePath;
            }
        }
    }

    return materials;
}

void Model::loadModel(const std::string& path)
{
    std::vector<glm::vec3> temp_positions;
    std::vector<glm::vec3> temp_normals;
    std::vector<glm::vec2> temp_texcoords;

    std::ifstream file(path);
    if (!file.is_open()) {
        std::cerr << "Failed to open model file: " << path << std::endl;
        return;
    }

    std::unordered_map<std::string, unsigned int> uniqueVertices;
    std::unordered_map<std::string, std::vector<Vertex>> materialVertices;
    std::unordered_map<std::string, std::vector<unsigned int>> materialIndices;

    std::string currentMaterial = "default";
    materials.clear();

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream ss(line);
        std::string prefix;
        ss >> prefix;

        if (prefix == "mtllib") {
            std::string mtlFileName;
            ss >> mtlFileName;
            std::string fullMtlPath = directory + "/" + mtlFileName;
            materials = loadMTL(fullMtlPath);  
        }
        else if (prefix == "usemtl") {
            ss >> currentMaterial;
            uniqueVertices.clear();
        }
        else if (prefix == "v") {
            float x, y, z;
            ss >> x >> y >> z;
            temp_positions.emplace_back(x, y, z);
        }
        else if (prefix == "vt") {
            float u, v;
            ss >> u >> v;
            temp_texcoords.emplace_back(u, v);
        }
        else if (prefix == "vn") {
            float x, y, z;
            ss >> x >> y >> z;
            temp_normals.emplace_back(x, y, z);
        }
        else if (prefix == "f") {
            std::vector<unsigned int> faceIndices;
            std::string vertexStr;
            while (ss >> vertexStr) {
                if (uniqueVertices.count(vertexStr) == 0) {
                    int vIdx = -1, vtIdx = -1, vnIdx = -1;
                    size_t pos1 = vertexStr.find('/');
                    size_t pos2 = vertexStr.find('/', pos1 + 1);

                    std::string vStr = vertexStr.substr(0, pos1);
                    std::string vtStr = (pos1 != std::string::npos && pos2 != std::string::npos)
                                          ? vertexStr.substr(pos1 + 1, pos2 - pos1 - 1)
                                          : "";
                    std::string vnStr = (pos2 != std::string::npos)
                                          ? vertexStr.substr(pos2 + 1)
                                          : "";

                    if (!vStr.empty()) vIdx = std::stoi(vStr) - 1;
                    if (!vtStr.empty()) vtIdx = std::stoi(vtStr) - 1;
                    if (!vnStr.empty()) vnIdx = std::stoi(vnStr) - 1;

                    Vertex vertex;
                    vertex.Position = vIdx >= 0 ? temp_positions[vIdx] : glm::vec3(0.0f);
                    vertex.TexCoords = vtIdx >= 0 ? temp_texcoords[vtIdx] : glm::vec2(0.0f);
                    vertex.Normal = vnIdx >= 0 ? temp_normals[vnIdx] : glm::vec3(0.0f);
                    vertex.Color = materials.count(currentMaterial) ? materials[currentMaterial].diffuseColor : glm::vec3(1.0f);

                    materialVertices[currentMaterial].push_back(vertex);
                    uniqueVertices[vertexStr] = static_cast<unsigned int>(materialVertices[currentMaterial].size() - 1);
                }

                faceIndices.push_back(uniqueVertices[vertexStr]);
            }

            for (size_t i = 1; i + 1 < faceIndices.size(); ++i) {
                materialIndices[currentMaterial].push_back(faceIndices[0]);
                materialIndices[currentMaterial].push_back(faceIndices[i]);
                materialIndices[currentMaterial].push_back(faceIndices[i + 1]);
            }
        }
    }

    file.close();

    // Inside loadModel()
    for (auto& pair : materialVertices) {
        const std::string& matName = pair.first;
        std::vector<Vertex>& verts = pair.second;
        std::vector<unsigned int>& inds = materialIndices[matName];

        Texture texture = std::move(diffuseTexture);  // fallback

        if (materials.count(matName) && !materials[matName].diffuseTexPath.empty()) {
            std::string texFullPath = directory + "/" + materials[matName].diffuseTexPath;
            texture = Texture(texFullPath);
        }

        meshes.emplace_back(std::move(verts), std::move(inds), std::move(texture));
    }
}
