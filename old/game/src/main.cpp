// Core includes
#include <iostream>
#include <filesystem>

#include "Shader.h"
#include "Window.h"
#include "DeltaTime.h"
#include "ImGuiSettings.h"
#include "Camera.h"
#include "Texture.h"
#include "Mesh.h"
#include "Model.h"   

// OpenGL
#include "GLFW/glfw3.h"
#include "glm/vec4.hpp"
#include <glm/gtc/matrix_transform.hpp>

int height = 800;
int width = 800;

Camera* Gptr_camera = nullptr;

void window_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
    if (Gptr_camera) {
        Gptr_camera->UpdateResolution(width, height);
    }
}

unsigned int lightIndices[] = {
    0, 1, 2, 0, 2, 3,
    0, 4, 7, 0, 7, 3,
    3, 7, 6, 3, 6, 2,
    2, 6, 5, 2, 5, 1,
    1, 5, 4, 1, 4, 0,
    4, 5, 6, 4, 6, 7
};

int main() {
    Window window(height, width, "SkyLands");
    ImGuiSettings IMGUI(window.GetWindow());

    glfwSetWindowSizeCallback(window.GetWindow(), window_size_callback);

    Camera camera(window.GetWindow(), height, width);
    Gptr_camera = &camera;


    Shader shader;
    shader.LoadShaders("../../SKY/game/Shaders/light.vert", "../../SKY/game/Shaders/light.frag");



    std::vector<float> modelData = ModelLoader::LoadOBJ("/home/fly/Documents/test/Resorces/test.obj");

    Mesh mesh(modelData);

    glEnable(GL_DEPTH_TEST);

    while (!window.ShouldClose()) {
        updateDeltaTime();
        glClearColor(0.4f, 0.23f, 0.35f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

        camera.UpdateMatrix();
        camera.KeyInput(shader);

        shader.Activate();
   
        shader.Activate();
        shader.setVec3("color", glm::vec3(1.0f, 0.0f, 1.0f));  // pink
        mesh.Draw(shader);
        // model.Draw(shaderProgram, camera);

// 
        // lightShader.Activate();
        // lightShader.setMat4("model", lightModel);
        // light.Draw(lightShader, camera);

        IMGUI.Update();
        window.SwapBuffers();
        window.PollEvents();
    }

    IMGUI.Shutdown();
    shader.Delete();

    return 0;
}

/*

        glm::mat4 objectModel = glm::mat4(1.0f); // identity or your model transform

        shaderProgram.setMat4("model", objectModel);
        shaderProgram.setFloat("material.shininess", 32.0f);
        // shaderProgram.setVec3("dirLight.direction", glm::vec3(-0.2f, -1.0f, -0.3f));
        // shaderProgram.setVec3("dirLight.ambient", glm::vec3(0.05f));
        // shaderProgram.setVec3("dirLight.diffuse", glm::vec3(0.4f));
        // shaderProgram.setVec3("dirLight.specular", glm::vec3(0.5f));

        shaderProgram.setVec3("pointLight.position", lightPos);
        shaderProgram.setFloat("pointLight.constant", 1.0f);
        shaderProgram.setFloat("pointLight.linear", 0.09f);
        shaderProgram.setFloat("pointLight.quadratic", 0.032f);
        shaderProgram.setVec3("pointLight.ambient", glm::vec3(0.05f));
        shaderProgram.setVec3("pointLight.diffuse", glm::vec3(0.8f));
        shaderProgram.setVec3("pointLight.specular", glm::vec3(1.0f));

        // shaderProgram.setVec3("spotLight.position", camera.Position);
        // shaderProgram.setVec3("spotLight.direction", camera.Orientation);
        // shaderProgram.setFloat("spotLight.cutOff", glm::cos(glm::radians(12.5f)));
        // shaderProgram.setFloat("spotLight.outerCutOff", glm::cos(glm::radians(17.5f)));
        // shaderProgram.setFloat("spotLight.constant", 1.0f);
        // shaderProgram.setFloat("spotLight.linear", 0.09f);
        // shaderProgram.setFloat("spotLight.quadratic", 0.032f);
        // shaderProgram.setVec3("spotLight.ambient", glm::vec3(0.0f));
        // shaderProgram.setVec3("spotLight.diffuse", glm::vec3(1.0f));
        // shaderProgram.setVec3("spotLight.specular", glm::vec3(1.0f));
*/