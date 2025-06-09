#ifndef MODEL_H
#define MODEL_H

#include <vector>
#include <string>
class ModelLoader {
public:
    // Loads model into a flat float array: pos (3) + texcoord (2) + normal (3)
    static std::vector<float> LoadOBJ(const std::string& path);
};

#endif // MODEL_H