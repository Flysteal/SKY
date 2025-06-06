// Model.cpp
#include "Model.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <unordered_map>
#include <algorithm>

bool Model::LoadFromOBJ(const std::string& filepath) {
    std::ifstream file(filepath);
    if (!file.is_open()) {
        std::cerr << "Failed to open OBJ file: " << filepath << "\n";
        return false;
    }

    std::vector<glm::vec3> tempPositions;
    std::vector<glm::vec2> tempTexCoords;
    std::vector<glm::vec3> tempNormals;

    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::unordered_map<std::string, unsigned int> uniqueVertexMap;
    unsigned int indexCounter = 0;

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string prefix;
        iss >> prefix;

        if (prefix == "v") {
            glm::vec3 pos;
            iss >> pos.x >> pos.y >> pos.z;
            tempPositions.push_back(pos);
        } else if (prefix == "vt") {
            glm::vec2 uv;
            iss >> uv.x >> uv.y;
            tempTexCoords.push_back(uv);
        } else if (prefix == "vn") {
            glm::vec3 norm;
            iss >> norm.x >> norm.y >> norm.z;
            tempNormals.push_back(norm);
        } else if (prefix == "f") {
            for (int i = 0; i < 3; ++i) {
                std::string vData;
                iss >> vData;

                if (uniqueVertexMap.count(vData) == 0) {
                    std::replace(vData.begin(), vData.end(), '/', ' ');
                    std::istringstream vss(vData);

                    int posIdx = 0, texIdx = 0, normIdx = 0;
                    vss >> posIdx >> texIdx >> normIdx;

                    Vertex vertex;
                    vertex.position = tempPositions[posIdx - 1];
                    vertex.texCoord = texIdx > 0 ? tempTexCoords[texIdx - 1] : glm::vec2(0.0f);
                    vertex.normal   = normIdx > 0 ? tempNormals[normIdx - 1] : glm::vec3(0.0f, 1.0f, 0.0f);

                    vertices.push_back(vertex);
                    uniqueVertexMap[vData] = indexCounter++;
                }

                indices.push_back(uniqueVertexMap[vData]);
            }
        }
    }

std::vector<Texture> textures;  // empty for now
meshes.emplace_back(vertices, indices, textures);



    std::cout << "Loaded model: " << filepath << "\n";
    std::cout << "Mesh count: " << meshes.size() << "\n";
    return true;
}

void Model::Draw(Shader& shader, Camera& camera)
{
    for (auto& mesh : meshes)
        mesh.Draw(shader, camera);
}

