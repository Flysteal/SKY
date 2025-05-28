#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "Camera.h"
#include "Shader.h"
#include "DeltaTime.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

Camera::Camera(GLFWwindow* window,  int width, int height)
    : InputManager(window), width(width), height(height)
{
    // Initialize yaw and pitch to your defaults
    yaw = -90.0f;
    pitch = 0.0f;
    cursorVisible = false;        // Start with cursor hidden and locked
    escapePressedLastFrame = false;

    // Initially lock and hide cursor
    glfwSetInputMode(k_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    ClearMousePos();
}

Camera::~Camera() = default;

void Camera::UpdateResolution(int newWidth, int newHeight)
{
    width = newWidth;
    height = newHeight;
}

void Camera::UpdateMatrix()
{
    float aspectRatio = static_cast<float>(width) / static_cast<float>(height);
    glm::mat4 view = glm::lookAt(Position, Position + Orientation, Up); 
    glm::mat4 projection = glm::perspective(glm::radians(fov), aspectRatio, 0.1f, 50.0f);
    camMatrix = projection * view;
}

void Camera::Matrix(Shader& shader, const char* uniform)
{
    glUniformMatrix4fv(glGetUniformLocation(shader.ID, uniform), 1, GL_FALSE, glm::value_ptr(camMatrix));
}

void Camera::KeyInput(Shader& shader)
{
    float Speed = camSpeed * deltaTime;

    glm::vec3 flatOrientation = glm::normalize(glm::vec3(Orientation.x, 0.0f, Orientation.z));
    glm::vec3 flatRight = glm::normalize(glm::cross(flatOrientation, Up));
    // Normalize Up vector to ensure consistent movement
    glm::vec3 normalizedUp = glm::normalize(Up);

    glm::vec3 moveDir(0.0f);
    if (IsKeyPressed(GLFW_KEY_W)) moveDir += flatOrientation;
    if (IsKeyPressed(GLFW_KEY_S)) moveDir -= flatOrientation;
    if (IsKeyPressed(GLFW_KEY_A)) moveDir -= flatRight;
    if (IsKeyPressed(GLFW_KEY_D)) moveDir += flatRight;
    if (IsKeyPressed(GLFW_KEY_SPACE)) moveDir += normalizedUp;
    if (IsKeyPressed(GLFW_KEY_LEFT_SHIFT)) moveDir -= normalizedUp;

    if (glm::length(moveDir) > 0.0f) Position += glm::normalize(moveDir) * Speed;


    // Toggle polygon mode on pressing 1 once
    if (IsKeyPressedOnce(GLFW_KEY_1)) {
        static bool wireframe = false;
        wireframe = !wireframe;
        glPolygonMode(GL_FRONT_AND_BACK, wireframe ? GL_LINE : GL_FILL);
    }

    if (IsKeyPressed(GLFW_KEY_F)) {
        if (IsKeyPressedOnce(GLFW_KEY_2))
            shader.LoadShaders("../../SKY/game/Shaders/default.vert", "../../SKY/game/Shaders/default.frag");
        if (IsKeyPressedToggle(GLFW_KEY_3)){
            shader.LoadShaders("../../SKY/game/Shaders/new.vert", "/home/flysteal/Desktop/SKY/game/Shaders/Dif_Point_Spot/spot.frag");
        }
        if (IsKeyPressedOnce(GLFW_KEY_4))
            shader.LoadShaders("../../SKY/game/Shaders/light.vert", "../../SKY/game/Shaders/light.frag");
        if (IsKeyPressedOnce(GLFW_KEY_5))
            shader.LoadShaders("../../SKY/game/Shaders/new.vert", "../../SKY/game/Shaders/new.frag");
    }
    // ESC key toggles cursor mode and mouse control
    bool escapePressed = IsKeyPressed(GLFW_KEY_ESCAPE);
    if (escapePressed && !escapePressedLastFrame) {
        cursorVisible = !cursorVisible;
        if (cursorVisible) {
            glfwSetInputMode(k_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);  // Show cursor
        } else {
            glfwSetInputMode(k_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED); // Hide & lock cursor
            ResetMousePos();  // Reset mouse delta so no jump on next move
        }
    }
    escapePressedLastFrame = escapePressed;

    // Update orientation only if cursor is hidden
    if (!cursorVisible) {
        MouseInput();
    }
}

void Camera::MouseInput()
{
    UpdateMousePosition();  // Get current mouse pos and delta

    double dx, dy;
    GetMouseDelta(dx, dy);

    yaw += static_cast<float>(dx) * sensitivity;
    pitch += static_cast<float>(dy) * sensitivity;

    pitch = glm::clamp(pitch, -89.0f, 89.0f);

    glm::vec3 front;
    front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    front.y = sin(glm::radians(pitch));
    front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    Orientation = glm::normalize(front);

    MouseScroll(fov, MouseSensitivity, false);//false means we use the x offset
    fov = glm::clamp(fov, 1.0f, 90.0f);

}
