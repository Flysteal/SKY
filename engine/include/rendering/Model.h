// Model.h
#pragma once

#include <string>
#include <vector>
#include "Mesh.h" // includes Vertex definition too

class Model {
public:
    bool LoadFromOBJ(const std::string& filepath);

    void Draw(Shader& shader, Camera& camera);  // in header and source


private:
    std::vector<Mesh> meshes;
};
