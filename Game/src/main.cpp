#include <iostream>

// #include "Texture.h"//glad
#include "Mesh.h"
#include "Model.h"
#include "Window.h"
#include "DeltaTime.h"
#include "Shader.h"
#include "Camera.h"
#include "ImGuiSettings.h"


#include "glad/gl.h"
#include "GLFW/glfw3.h"

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

    Shader shader;
    shader.LoadShaders("../../SKY/Game/Shaders/new.vert",
                       "../../SKY/Game/Shaders/new.frag");

    Camera camera(window.GetWindow(), width, height);
    Gptr_camera = &camera;
    glfwSetWindowSizeCallback(window.GetWindow(), window_size_callback);

float cords[12]={
  0.0f, 1.0f, 1.0f,
  1.0f, 0.0f, 1.0f,
  1.0f, 1.0f, 0.0f,
  1.0f, 0.0f, 1.0f
};

    Model cubeObj("/home/fly/Documents/SKY/Game/RSC/cube.obj");
    cubeObj.Translate(glm::vec3(cords[0], cords[1], cords[2]));

    Model TeaPotObj("/home/fly/Documents/SKY/Game/RSC/TeaPot.obj");
    TeaPotObj.Translate(glm::vec3(cords[3], cords[4], cords[5]));

    Model BallObj("/home/fly/Documents/SKY/Game/RSC/ball.obj");
    BallObj.Translate(glm::vec3(cords[6], cords[7], cords[8]));

    Model Island("/home/fly/Documents/SKY/Game/RSC/DeathsIsland/DeathsIsland.obj");
    Island.Translate(glm::vec3(cords[9], cords[10], cords[11]));

    glEnable(GL_DEPTH_TEST);
    while (!window.ShouldClose())
    {
        UpdateDeltaTime(window.GetTime());

        glClearColor(0.3f, 0.2f, 0.2f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        camera.UpdateMatrix();
        camera.KeyInput(shader);

        shader.Use();
        shader.setMat4("camMatrix", camera.GetCamMatrix());
    cubeObj.Translate(glm::vec3(cords[0], cords[1], cords[2]));

        shader.setMat4("model", cubeObj.Matrix);
        shader.setBool("useTexture", true);
        cubeObj.Draw(shader);
    TeaPotObj.Translate(glm::vec3(cords[3], cords[4], cords[5]));

        shader.setMat4("model", TeaPotObj.Matrix);
        shader.setBool("useTexture", false);
        TeaPotObj.Draw(shader);
    BallObj.Translate(glm::vec3(cords[6], cords[7], cords[8]));

        shader.setMat4("model", BallObj.Matrix);
        shader.setBool("useTexture", false);
        BallObj.Draw(shader);
    Island.Translate(glm::vec3(cords[9], cords[10], cords[11]));

        shader.setMat4("model", Island.Matrix);
        shader.setBool("useTexture", false);
        Island.Draw(shader);

        IMGUI.Update();
        window.SwapBuffers();
        window.PollEvents();
    }

    IMGUI.Shutdown();
    shader.Delete();
    return 0;
}