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
    : InputManager(window), shader(shaderRef), width(width), height(height) {}

Camera::~Camera() = default;

void Camera::UpdateResolution(int newWidth, int newHeight)
{
    width = newWidth;
    height = newHeight;
}

void Camera::Matrix(const char* uniform)
{
    // const float radius = 10.0f;
    // float camX = sin(glfwGetTime()) * radius;
    // float camZ = cos(glfwGetTime()) * radius;
    float aspectRatio = static_cast<float>(width) / static_cast<float>(height);

    glm::mat4 view = glm::lookAt(Position, Position + Orientation, Up); 

    glm::mat4 proj = glm::perspective(glm::radians(45.0f), static_cast<float>(width)/static_cast<float>(height), 0.1f, 100.0f);
    glm::mat4 projection = glm::perspective(glm::radians(45.0f), aspectRatio, 0.1f, 50.0f);
    glm::mat4 camMatrix = projection * view;
    glUniformMatrix4fv(glGetUniformLocation(shader.ID, uniform), 1, GL_FALSE, glm::value_ptr(camMatrix));
}


void Camera::KeyInput()
{
    static float Speed;
    Speed = camSpeed * deltaTime;

    glm::vec3 right = glm::normalize(glm::cross(Orientation, Up));

    if(IsKeyPressed(GLFW_KEY_W)){
        Position += Speed * Orientation ;
    }
    if(IsKeyPressed(GLFW_KEY_A)){
        Position -= right * deltaTime;
    }
    if(IsKeyPressed(GLFW_KEY_S)){
        Position -= Speed * Orientation ;
    }
    if(IsKeyPressed(GLFW_KEY_D)){
        Position += right * deltaTime;
    }

    if(IsKeyPressed(GLFW_KEY_F))
    {
        if (IsKeyPressedOnce(GLFW_KEY_1))
        { shader.LoadShaders("../../SKY/game/Shaders/default.vert", "../../SKY/game/Shaders/default.frag");}

        if (IsKeyPressedOnce(GLFW_KEY_2))
        { shader.LoadShaders("../../SKY/game/Shaders/light.vert", "../../SKY/game/Shaders/light.frag");}

        if (IsKeyPressedOnce(GLFW_KEY_3))
        { shader.LoadShaders("../../SKY/game/Shaders/mTextures.vert", "../../SKY/game/Shaders/mTextures.frag");}

        if (IsKeyPressedOnce(GLFW_KEY_4))
        { shader.LoadShaders("../../SKY/game/Shaders/glm.vert", "../../SKY/game/Shaders/glm.frag");}
    }

    if (IsKeyPressedOnce(GLFW_KEY_1)){
        static bool a = false;  a = !a;

        a ? glPolygonMode(GL_FRONT_AND_BACK, GL_LINE) :  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }
}

void Camera::MouseInput()
{
    if (IsMouseButtonPressedOnce(GLFW_MOUSE_BUTTON_2))
    std::cout << "hi from 2\n";

    if (IsMouseButtonPressedOnce(GLFW_MOUSE_BUTTON_1)){
    std::cout << "hi from 1\n";
        Position = glm::vec3{0.0f, 0.0f, 1.0f};
    }
}

// Camera::GetPosition = Position;

// IsKeyPressed         IsKeyPressedOnce        IsKeyPressedToggle 
// IsMouseButtonPressed IsMouseButtonPressedOnce IsMouseButtonPressedToggle