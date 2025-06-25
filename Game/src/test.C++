#include <iostream>

#include "ImGuiSettings.h"
#include "DeltaTime.h"
#include "Window.h"
#include "Shader.h"
#include "Camera.h"

#include "Model.h"

#include "glad/gl.h"
#include "GLFW/glfw3.h"
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


int main()
{
    Window window("SkyLands", width, height);

    ImGuiSettings IMGUI(window.GetWindow());

    Shader shader("../../SKY/Game/Shaders/color.vert", "../../SKY/Game/Shaders/color.frag");
    Shader shaderOutline("../../SKY/Game/Shaders/new.vert", "../../SKY/Game/Shaders/new.frag");
    // time to load ~ 0.0304952

    Camera camera(window.GetWindow(), width, height);
    Gptr_camera = &camera;
    // time to load ~ 3.5870002

    glfwSetWindowSizeCallback(window.GetWindow(), window_size_callback);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);  

    glEnable(GL_STENCIL_TEST);    

    Model model1("../../SKY/Game/RSC/CubeRGBA/Cube.obj");
    Model model2("../../SKY/Game/RSC/Grass/Grass.obj");
    Model model3("../../SKY/Game/RSC/Ground/Ground.obj");

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); 
    


    while (!window.ShouldClose())
    {
        UpdateDeltaTime(window.GetTime());

        glClearColor(0.58f, 0.855f, 0.902f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT); 

        camera.UpdateMatrix();
        camera.KeyInput(shader);

// {
            // Draw model write to stencil
            glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE); // Keep stencil unless fragment passes
            glStencilFunc(GL_ALWAYS, 1, 0xFF);         // Always pass stencil test
            glStencilMask(0xFF);                       // Enable writing to stencil
// }
        shader.Use();
        model3.SetTransform(glm::vec3(1.0f, 0.0f, 1.0f), glm::vec3(0.0f), glm::vec3(0.5f));
        shader.setMat4("camMatrix", camera.GetCamMatrix());
        shader.setMat4("model", model1.Matrix);
        model1.Draw(shader);
// {
            // Draw outline, but only where stencil != 1
            glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
            glStencilMask(0x00); // Disable writing to stencil
            glDisable(GL_DEPTH_TEST);

            shaderOutline.Use();
            glm::mat4 scaledModel = glm::scale(model1.Matrix, glm::vec3(1.1f));
            shaderOutline.setMat4("camMatrix", camera.GetCamMatrix());
            shaderOutline.setMat4("model", scaledModel);
            model1.Draw(shaderOutline);

            // Reset stencil and depth state
            glStencilMask(0xFF);
            glStencilFunc(GL_ALWAYS, 0, 0xFF);
            glEnable(GL_DEPTH_TEST);
// }

        shader.Use();
        shader.setMat4("camMatrix", camera.GetCamMatrix());
        model2.SetTransform(glm::vec3(10.0f, 0.0f, 0.0f), glm::vec3(0.0f), glm::vec3(1.0f));
        shader.setMat4("model", model2.Matrix);
        model2.Draw(shader);

        shader.Use();
        model3.SetTransform(glm::vec3(0.0f, 24.5f, 0.0f), glm::vec3(0.0f), glm::vec3(50.0f));
        shader.setMat4("camMatrix", camera.GetCamMatrix());
        shader.setMat4("model", model3.Matrix);
        model3.Draw(shader);


        IMGUI.Update();
        window.SwapBuffers();
        window.PollEvents();
    }


    IMGUI.Shutdown();
    shader.Delete();
    return 0;
}

    // Shader shaderOutline("../../SKY/Game/Shaders/new.vert", "../../SKY/Game/Shaders/new.frag");


    // Model model2("../../SKY/Game/RSC/Grass/Grass.obj");
    // Model model3("../../SKY/Game/RSC/Ground/Ground.obj");

        // shader.Use();
        // shader.setMat4("camMatrix", camera.GetCamMatrix());
        // model2.SetTransform(glm::vec3(10.0f, 0.0f, 0.0f), glm::vec3(0.0f), glm::vec3(1.0f));
        // shader.setMat4("model", model2.Matrix);
        // model2.Draw(shader);

        // shader.Use();
        // model3.SetTransform(glm::vec3(0.0f, 24.5f, 0.0f), glm::vec3(0.0f), glm::vec3(50.0f));
        // shader.setMat4("camMatrix", camera.GetCamMatrix());
        // shader.setMat4("model", model3.Matrix);
        // model3.Draw(shader);