#ifndef SHADER_H
#define SHADER_H

#include <string>
#include <glm/mat4x4.hpp>


class Shader {
public:
    Shader();
    ~Shader();

    unsigned int ID;

    static std::string fileContent(const std::string& filePath);

    void Activate() const;
    void LoadShaders(const char* vertexFile, const char* fragmentFile);
    void Delete();

    void SetMat4(const std::string &name, const glm::mat4 &mat);
    void setVec3(const std::string &name, const glm::vec3 &value) const;
    void setVec3(const std::string &name, float x, float y, float z) const;


private:
    void compileErrors(unsigned int shader, const char* type) const;
};

#endif