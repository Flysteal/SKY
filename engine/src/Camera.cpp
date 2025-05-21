#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "Camera.h"
#include "Shader.h"
#include "DeltaTime.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

Camera::Camera(GLFWwindow* window, Shader& shaderRef, int width, int height)
    : InputManager(window), shader(shaderRef), width(width), height(height)
{
    // Initialize yaw and pitch to your defaults
    yaw = -90.0f;
    pitch = 0.0f;
    cursorVisible = false;        // Start with cursor hidden and locked
    escapePressedLastFrame = false;

    // Initially lock and hide cursor
    glfwSetInputMode(k_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

Camera::~Camera() = default;

void Camera::UpdateResolution(int newWidth, int newHeight)
{
    width = newWidth;
    height = newHeight;
}

void Camera::Matrix(const char* uniform)
{
    float aspectRatio = static_cast<float>(width) / static_cast<float>(height);
    glm::mat4 view = glm::lookAt(Position, Position + Orientation, Up); 
    glm::mat4 projection = glm::perspective(glm::radians(45.0f), aspectRatio, 0.1f, 50.0f);
    glm::mat4 camMatrix = projection * view;
    glUniformMatrix4fv(glGetUniformLocation(shader.ID, uniform), 1, GL_FALSE, glm::value_ptr(camMatrix));
}

void Camera::KeyInput()
{
    float Speed = camSpeed * deltaTime;
    glm::vec3 right = glm::normalize(glm::cross(Orientation, Up));

    if (IsKeyPressed(GLFW_KEY_W)) Position += Speed * Orientation;
    if (IsKeyPressed(GLFW_KEY_A)) Position -= right * Speed;
    if (IsKeyPressed(GLFW_KEY_S)) Position -= Speed * Orientation;
    if (IsKeyPressed(GLFW_KEY_D)) Position += right * Speed;

    // Toggle polygon mode on pressing 1 once
    if (IsKeyPressedOnce(GLFW_KEY_1)) {
        static bool wireframe = false;
        wireframe = !wireframe;
        glPolygonMode(GL_FRONT_AND_BACK, wireframe ? GL_LINE : GL_FILL);
    }

    // Shader loading shortcuts (F + 1..4)
    if (IsKeyPressed(GLFW_KEY_F)) {
        if (IsKeyPressedOnce(GLFW_KEY_1))
            shader.LoadShaders("../../SKY/game/Shaders/default.vert", "../../SKY/game/Shaders/default.frag");
        if (IsKeyPressedOnce(GLFW_KEY_2))
            shader.LoadShaders("../../SKY/game/Shaders/light.vert", "../../SKY/game/Shaders/light.frag");
        if (IsKeyPressedOnce(GLFW_KEY_3))
            shader.LoadShaders("../../SKY/game/Shaders/mTextures.vert", "../../SKY/game/Shaders/mTextures.frag");
        if (IsKeyPressedOnce(GLFW_KEY_4))
            shader.LoadShaders("../../SKY/game/Shaders/glm.vert", "../../SKY/game/Shaders/glm.frag");
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

    // Update orientation only if cursor is hidden (locked)
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
}
