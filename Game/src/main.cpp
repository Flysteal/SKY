#include <iostream>

// #include "Texture.h"//glad
#include "Mesh.h"
#include "Model.h"
#include "Window.h"
#include "DeltaTime.h"
#include "Shader.h"
#include "Camera.h"


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

    Shader shader;
    shader.LoadShaders("../../SKY/Game/Shaders/new.vert",
                       "../../SKY/Game/Shaders/new.frag");

    Camera camera(window.GetWindow(), width, height);
    Gptr_camera = &camera;
    glfwSetWindowSizeCallback(window.GetWindow(), window_size_callback);


    Model cubeObj("/home/fly/Documents/SKY/Game/RSC/cube.obj");
    cubeObj.Translate(glm::vec3(3.0f, 0.0f, 0.0f));

    // Model TeaPotObj("/home/fly/Documents/SKY/Game/RSC/DeathsIsland/DeathsIsland.obj");
    // TeaPotObj.Translate(glm::vec3(1.0f, 0.0f, 3.0f));

    // Model BallObj("/home/fly/Documents/SKY/Game/RSC/ball.obj");
    // BallObj.Translate(glm::vec3(-1.0f, 0.0f, 2.0f));

    // Model ColorCube("/home/fly/Documents/SKY/Game/RSC/colorCube.obj");
    // ColorCube.Translate(glm::vec3(0.0, 0.0, 0.0));

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

        shader.setMat4("model", cubeObj.Matrix);
        shader.setBool("useTexture", false); // or false to use vertex color
        cubeObj.Draw(shader);

        // shader.setMat4("model", TeaPotObj.Matrix);
        // shader.setBool("useTexture", false); // or false to use vertex color
        // TeaPotObj.Draw(shader);

        // shader.setMat4("model", ColorCube.Matrix);
        // shader.setBool("useTexture", false); // or false to use vertex color
        // ColorCube.Draw(shader);

        // shader.setMat4("model", BallObj.Matrix);
        // BallObj.Draw(shader);


        window.SwapBuffers();
        window.PollEvents();
    }

    return 0;
}