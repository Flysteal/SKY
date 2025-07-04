#ifndef SHADER_H
#define SHADER_H

#include <string>
#include <glm/glm.hpp>


class Shader {
public:
    Shader(const char* vertexFile, const char* fragmentFile);
    ~Shader();

    unsigned int ID;

    static std::string fileContent(const std::string& filePath);

    void Use() const;
    void LoadShaders(const char* vertexFile, const char* fragmentFile);

    void Delete();

    void setBool(const std::string &name, bool value) const;
    void setInt(const std::string& name, int value) const;
    void setFloat(const std::string &name, float value) const;
    void setVec2(const std::string &name, const glm::vec2 &value) const;
    void setVec2(const std::string &name, float x, float y) const;
    void setVec3(const std::string &name, const glm::vec3 &value) const;
    void setVec3(const std::string &name, float x, float y, float z) const;
    void setVec4(const std::string &name, const glm::vec4 &value) const;
    void setVec4(const std::string &name, float x, float y, float z, float w) const;
    void setMat2(const std::string &name, const glm::mat2 &mat) const;
    void setMat3(const std::string &name, const glm::mat3 &mat) const;
    void setMat4(const std::string &name, const glm::mat4 &mat) const;


private:
    void compileErrors(unsigned int shader, const char* type) const;
};

#endif