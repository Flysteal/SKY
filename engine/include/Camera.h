#ifndef CAMERA_H
#define CAMERA_H

#include "InputManager.h"
#include "glm/vec3.hpp"
struct GLFWwindow;
class Shader;


class Camera : private InputManager {
public:

    Camera(GLFWwindow* window, Shader& shaderRef, int width, int height);
    ~Camera();
    void MouseInput();
    void KeyInput();

    void UpdateResolution(int newWidth, int newHeight);
    void Matrix(const char* uniform);

private:
    Shader& shader;
    int height, width;

    bool cursorVisible = false;
    bool escapePressedLastFrame = false;
    float yaw = -90.0f;
    float pitch = 0.0f;
    float sensitivity = 0.1f;


    float camSpeed = 2.2;

    glm::vec3 Position = glm::vec3(0.0f, 0.0f, 2.0f);
    glm::vec3 Orientation = glm::vec3(0.0f, 0.0f, -1.0f);
    glm::vec3 Up = glm::vec3(0.0f, 1.0f, 0.0f);
};

#endif