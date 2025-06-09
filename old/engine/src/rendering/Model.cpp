#include "Model.h"
#include <fstream>
#include <sstream>
#include <iostream>

std::vector<float> ModelLoader::LoadOBJ(const std::string& path) {
    std::ifstream file(path);
    if (!file.is_open()) {
        std::cerr << "Failed to open OBJ file: " << path << "\n";
        return {};
    }

    std::vector<float> positions;
    std::vector<float> texcoords;
    std::vector<float> normals;
    std::vector<float> result;

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream ss(line);
        std::string prefix;
        ss >> prefix;

        if (prefix == "v") {
            float x, y, z;
            ss >> x >> y >> z;
            positions.insert(positions.end(), { x, y, z });
        } else if (prefix == "vt") {
            float u, v;
            ss >> u >> v;
            texcoords.insert(texcoords.end(), { u, v });
        } else if (prefix == "vn") {
            float nx, ny, nz;
            ss >> nx >> ny >> nz;
            normals.insert(normals.end(), { nx, ny, nz });
        }else if (prefix == "f") {
    std::vector<std::string> verticesInFace;
    std::string vertexStr;
    while (ss >> vertexStr) {
        verticesInFace.push_back(vertexStr);
    }

    if (verticesInFace.size() < 3) continue; // invalid face

    // Parse all vertices indices in this face
    struct VertexIndices {
        int vi, ti, ni;
    };
    std::vector<VertexIndices> faceIndices;

    for (const auto& vStr : verticesInFace) {
        int vi = 0, ti = 0, ni = 0;
        sscanf(vStr.c_str(), "%d/%d/%d", &vi, &ti, &ni);
        faceIndices.push_back({vi, ti, ni});
    }

    // Triangulate face (triangle fan method)
    for (size_t i = 1; i + 1 < faceIndices.size(); ++i) {
        VertexIndices indices[3] = { faceIndices[0], faceIndices[i], faceIndices[i + 1] };
        for (int k = 0; k < 3; ++k) {
            int vi = (indices[k].vi - 1) * 3;
            int ti = (indices[k].ti - 1) * 2;
            int ni = (indices[k].ni - 1) * 3;

            if (vi < 0 || vi + 2 >= (int)positions.size()) continue;
            result.push_back(positions[vi + 0]);
            result.push_back(positions[vi + 1]);
            result.push_back(positions[vi + 2]);

            if (ti >= 0 && ti + 1 < (int)texcoords.size()) {
                result.push_back(texcoords[ti + 0]);
                result.push_back(texcoords[ti + 1]);
            } else {
                result.push_back(0.0f);
                result.push_back(0.0f);
            }

            if (ni >= 0 && ni + 2 < (int)normals.size()) {
                result.push_back(normals[ni + 0]);
                result.push_back(normals[ni + 1]);
                result.push_back(normals[ni + 2]);
            } else {
                result.push_back(0.0f);
                result.push_back(0.0f);
                result.push_back(0.0f);
            }
        }
    }
}

    }

    return result;
}
