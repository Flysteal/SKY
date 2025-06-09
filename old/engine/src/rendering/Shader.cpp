#ifndef FUNCS_H
#define FUNCS_H

#include "glad/gl.h"
#include "GLFW/glfw3.h"
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class func
{
public:
    func();
    ~func();

    void window();
    void PollEvents();
    void SwapBuffers();
    bool ShouldClose();
    void Delete();

    GLFWwindow* GetWindow();

private:
    GLFWwindow* m_Window;
};

class cShader
{
public:
    unsigned int ID;

    cShader(const std::string& filePath)
    {
        std::ifstream file(filePath);
        if (!file.is_open()) {
            std::cerr << filePath << ": Shader file could not be opened\n";
            return;
        }

        std::stringstream buffer;
        buffer << file.rdbuf();
        std::string cShaderCode = buffer.str();

        const char* source = cShaderCode.c_str();
        unsigned int CMP = glCreateShader(GL_COMPUTE_SHADER);
        glShaderSource(CMP, 1, &source, nullptr);
        glCompileShader(CMP);
        checkCompileErrors(CMP, "COMPUTE");

        ID = glCreateProgram();
        glAttachShader(ID, CMP);
        glLinkProgram(ID);
        checkCompileErrors(ID, "PROGRAM");

        glDeleteShader(CMP);
    }

private:
    void checkCompileErrors(unsigned int shader, const std::string& type)
    {
        int success;
        char infoLog[1024];
        if (type != "PROGRAM")
        {
            glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
            if (!success)
            {
                glGetShaderInfoLog(shader, 1024, NULL, infoLog);
                std::cerr << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n"
                          << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
            }
        }
        else
        {
            glGetProgramiv(shader, GL_LINK_STATUS, &success);
            if (!success)
            {
                glGetProgramInfoLog(shader, 1024, NULL, infoLog);
                std::cerr << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n"
                          << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
            }
        }
    }
};

#endif // FUNCS_H
