#ifndef MODEL_H
#define MODEL_H


#include <glm/glm.hpp>
// #include <string>

#include "Shader.h"
#include "Mesh.h"

class Model {
public:
    Model();
    void Draw(Shader& shader);

    void Translate(glm::vec3 vec);
    glm::mat4 Matrix = glm::mat4(1.0f);

private:
    std::vector<Mesh> meshes;
    void loadModel();
};


#endif // MODEL_H