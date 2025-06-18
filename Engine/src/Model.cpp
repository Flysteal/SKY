#include "Model.h"

#include "glad/gl.h"
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>

#include <fstream>
#include <sstream>
#include <iostream>
#include <map>


Model::Model(const std::string& path)
    : diffuseTexture("/home/fly/Documents/SKY/Game/RSC/brick.jpg")
{
    textures.push_back(diffuseTexture);
    loadModel(path);
}

void Model::Draw(Shader& shader)
{
    diffuseTexture.Bind(0);
    shader.setInt("texture_diffuse1", 0);
    for (Mesh& mesh : meshes) {
        mesh.Draw(shader);
    }
}

void Model::Translate(glm::vec3 vec)
{
    glm::mat4 setter = glm::mat4(1.0f);
    Matrix = glm::translate(setter, vec);
}


void Model::loadModel(const std::string& path)
{
    std::vector<glm::vec3> temp_positions;
    std::vector<glm::vec3> temp_normals;
    std::vector<glm::vec2> temp_texcoords;

    std::ifstream file(path);
    if (!file.is_open())
    {
        std::cerr << "Failed to open model file: " << path << std::endl;
        return;
    }

    std::map<std::string, unsigned int> uniqueVertices;

    std::string line;
    while (std::getline(file, line))
    {
        std::istringstream ss(line);
        std::string prefix;
        ss >> prefix;

        if (prefix == "v")
        {
            float x, y, z;
            ss >> x >> y >> z;
            temp_positions.emplace_back(x, y, z);
        }
        else if (prefix == "vt")
        {
            float u, v;
            ss >> u >> v;
            temp_texcoords.emplace_back(u, v);
        }
        else if (prefix == "vn")
        {
            float x, y, z;
            ss >> x >> y >> z;
            temp_normals.emplace_back(x, y, z);
        }
        else if (prefix == "f")
        {
            std::vector<unsigned int> faceIndices;

            std::string vertexStr;
            while (ss >> vertexStr)
            {
                if (uniqueVertices.count(vertexStr) == 0)
                {
                    // Same parsing as before
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
                    vertex.Color = glm::vec3(1.0f); // or from material

                    vertices.push_back(vertex);
                    uniqueVertices[vertexStr] = static_cast<unsigned int>(vertices.size() - 1);
                }

                faceIndices.push_back(uniqueVertices[vertexStr]);
            }
                // Triangulate polygon (supports triangle, quad, n-gon)
            for (size_t i = 1; i + 1 < faceIndices.size(); ++i)
            {
                indices.push_back(faceIndices[0]);
                indices.push_back(faceIndices[i]);
                indices.push_back(faceIndices[i + 1]);
            }
        }
    }

    file.close();

    if (vertices.empty() || indices.empty())
    {
        std::cerr << "Failed to parse OBJ properly." << std::endl;
        return;
    }

    meshes.emplace_back(vertices, indices);
}
