#ifndef CAMERA_H
#define CAMERA_H

#include "InputManager.h"
struct GLFWwindow;
class Shader;

#include "glm/vec3.hpp"

class Camera : private InputManager {
public:

    Camera(GLFWwindow* window, Shader& shader, int height, int width);
    void KeyInput();
    void MouseInput();


    void UpdateResolution(int newWidth, int newHeight);
    void Matrix(const char* uniform);


private:
    Shader& shader;
    int height, width;

    glm::vec3 Position = glm::vec3(0.0f, 0.0f, 2.0f);
    glm::vec3 Orientation = glm::vec3(0.0f, 0.0f, -1.0f);
    glm::vec3 Up = glm::vec3(0.0f, 1.0f, 0.0f);
};

#endif