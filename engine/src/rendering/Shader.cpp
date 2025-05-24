#include "Shader.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <glad/gl.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

Shader::Shader() = default;

Shader::~Shader(){ Delete(); }

void Shader::Activate() const {
    glUseProgram(ID);
}

void Shader::Delete() {
    glDeleteProgram(ID);
}


std::string Shader::fileContent(const std::string& filePath)
{
    std::ifstream file(filePath);
    if (!file.is_open()) {
        std::cerr << filePath << "Shader content error\n";
        return "";
    }
    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

void Shader::LoadShaders(const char* vertexFile, const char* fragmentFile) {
    Delete();
    if (!vertexFile || !fragmentFile) {
        std::cerr << "Null shader file path\n";
        return;
    }

    std::string vertexCode = fileContent(vertexFile);
    std::string fragmentCode = fileContent(fragmentFile);

    if (vertexCode.empty() || fragmentCode.empty()) {
        std::cerr << "Shader file empty or unreadable\n";
        return;
    }

    const char* vertexSource = vertexCode.c_str();
    const char* fragmentSource = fragmentCode.c_str();

    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexSource, NULL);
    glCompileShader(vertexShader);
    compileErrors(vertexShader, "VERTEX");

    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
    glCompileShader(fragmentShader);
    compileErrors(fragmentShader, "FRAGMENT");

    ID = glCreateProgram();
    glAttachShader(ID, vertexShader);
    glAttachShader(ID, fragmentShader);
    glLinkProgram(ID);
    compileErrors(ID, "PROGRAM");

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    std::cout << "-new shader\n";
}



void Shader::compileErrors(unsigned int shader, const char* type) const {
    GLint hasCompiled;
    char infoLog[1024];
    if (std::string(type) != "PROGRAM") {
        glGetShaderiv(shader, GL_COMPILE_STATUS, &hasCompiled);
        if (hasCompiled == GL_FALSE) {
            glGetShaderInfoLog(shader, 1024, NULL, infoLog);
            std::cerr << "SHADER_COMPILATION_ERROR for: " << type << "\n" << infoLog << std::endl;
            // throw std::runtime_error("Shader compilation error");
            // return;
        }
    } else {
        glGetProgramiv(shader, GL_LINK_STATUS, &hasCompiled);
        if (hasCompiled == GL_FALSE) {
            glGetProgramInfoLog(shader, 1024, NULL, infoLog);
            std::cerr << "SHADER_LINKING_ERROR for: " << type << "\n" << infoLog << std::endl;
            // std::cout << ("Shader linking error");
            // return;
        }
    }
}

void Shader::SetMat4(const std::string &name, const glm::mat4 &mat)
{
    glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, glm::value_ptr(mat));
}
//          ---
void Shader::setVec3(const std::string &name, const glm::vec3 &value) const
{ 
    glUniform3fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]); 
}
void Shader::setVec3(const std::string &name, float x, float y, float z) const
{ 
    glUniform3f(glGetUniformLocation(ID, name.c_str()), x, y, z); 
}
//          ---
void Shader::setFloat(const std::string &name, float value) const
{ 
    glUniform1f(glGetUniformLocation(ID, name.c_str()), value); 
}
//          ---