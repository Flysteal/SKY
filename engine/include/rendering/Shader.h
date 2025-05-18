#ifndef SHADER_H
#define SHADER_H

#include <string>

class Shader {
public:
    Shader();
    ~Shader();

    unsigned int ID;

    static std::string fileContent(const std::string& filePath);

    void Activate() const;
    void LoadShaders(const char* vertexFile, const char* fragmentFile);
    void Delete();

private:
    void compileErrors(unsigned int shader, const char* type) const;
};

#endif