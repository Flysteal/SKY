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

    Camera camera(window.GetWindow(), width, height);
    // time to load ~ 3.5870002
    Gptr_camera = &camera;

    glfwSetWindowSizeCallback(window.GetWindow(), window_size_callback);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);  

    glEnable(GL_STENCIL_TEST);    

    Model model1("../../SKY/Game/RSC/CubeRGBA/Cube.obj");


    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); 
    

    while (!window.ShouldClose())
    {
        UpdateDeltaTime(window.GetTime());

        glClearColor(0.58f, 0.855f, 0.902f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT); 

        camera.UpdateMatrix();
        camera.KeyInput(shader);

        shader.Use();
        // model1.SetTransform(glm::vec3(1.0f, 0.0f, 1.0f), glm::vec3(0.0f), glm::vec3(0.5f));
        shader.setMat4("camMatrix", camera.GetCamMatrix());
        shader.setMat4("model", model1.Matrix);
        // shader.setFloat("materialAlpha", materials.alpha);

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glDepthMask(GL_FALSE);
        model1.Draw(shader);
        glDepthMask(GL_TRUE);



        IMGUI.Update();
        window.SwapBuffers();
        window.PollEvents();
    }


    IMGUI.Shutdown();
    shader.Delete();
    return 0;
}