#ifndef MATERIAL_H
#define MATERIAL_H

#include <string>
#include "glm/vec3.hpp"

struct Material {
    glm::vec3 diffuseColor = glm::vec3(1.0f);
    std::string diffuseTexPath;
};

#endif
