#ifndef MATERIAL_H
#define MATERIAL_H

#include <string>

struct Material {
    std::string name;
    std::string diffuseTexPath; // map_Kd
    // You can add more if needed later, e.g. specular, ambient, etc.
};

#endif
