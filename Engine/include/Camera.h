#ifndef CAMERA_H
#define CAMERA_H

#include "InputManager.h"
#include "glm/vec3.hpp"
#include "glm/matrix.hpp"
struct GLFWwindow;
class Shader;


class Camera : private InputManager {
public:

    Camera(GLFWwindow* window, int width, int height);
    ~Camera();
    void MouseInput();
    void KeyInput(Shader& shader);

    void UpdateResolution(int newWidth, int newHeight);
    void UpdateMatrix();
    void Matrix(Shader& shader, const char* uniform);

    glm::vec3 Position = glm::vec3(0.0f, 0.2f, 2.0f);
    glm::vec3 Orientation = glm::vec3(0.0f, 0.0f, -1.0f);
    glm::mat4 camMatrix;
private:
    // Shader& shader;
    int height, width;

    bool cursorVisible = false;
    bool escapePressedLastFrame = false;
    float yaw = -90.0f;
    float pitch = 0.0f;
    float fov = 70.0;

    float sensitivity = 0.1f;
    float MouseSensitivity = 3.0f;

    float camSpeed = 2.2;

    glm::vec3 Up = glm::vec3(0.0f, 1.0f, 0.0f);

};

#endif