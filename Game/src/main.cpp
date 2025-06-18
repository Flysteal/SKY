#include <iostream>

#include "ImGuiSettings.h"
#include "DeltaTime.h"
#include "Window.h"
#include "Shader.h"
#include "Camera.h"

#include "Model.h"

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
    shader.LoadShaders("../../SKY/Game/Shaders/color.vert",
                       "../../SKY/Game/Shaders/color.frag");
    // time to load ~ 0.0304952

    Camera camera(window.GetWindow(), width, height);
    Gptr_camera = &camera;
    // time to load ~ 3.5870002
    glfwSetWindowSizeCallback(window.GetWindow(), window_size_callback);

    glEnable(GL_DEPTH_TEST);

    Model model1("/home/fly/Documents/SKY/Game/RSC/Cube/cube.obj");
    // time to load ~ 0.0003874 1 cords.txt     // time to load ~ 0.0606654 1 cube.obj     // time to load ~ 0.2431000 1 TeaPot.obj     // time to load ~ 2.4642400 1 ball.obj     // time to load ~ 47.838000 1 BigBall.obj


    while (!window.ShouldClose())
    {
        UpdateDeltaTime(window.GetTime());

        glClearColor(0.58f, 0.855f, 0.902f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT); 

        camera.UpdateMatrix();
        camera.KeyInput(shader);

        shader.Use();
        shader.setMat4("camMatrix", camera.GetCamMatrix());


        // shader.Use();
        // shader.setInt("diffuseTexture", 0);  // must match the GL_TEXTURE0 unit

        // // If your Texture class uses glBindTexture internally:
        // texture.Bind(0);  // this is called inside Mesh::Draw

        model1.Translate(glm::vec3(1.5f));
        shader.setMat4("model", model1.Matrix);
        // shader.setBool("useTexture", true);
        model1.Draw(shader);


        IMGUI.Update();
        window.SwapBuffers();
        window.PollEvents();
    }

    IMGUI.Shutdown();
    shader.Delete();
    return 0;
}