#include <iostream>

#include "Window.h"
#include "DeltaTime.h"
#include "Shader.h"
#include "Mesh.h"
#include "Model.h"
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

    std::vector<float> model1 = ModelLoader::LoadOBJ("../../SKY/Game/RSC/cube.obj");
    std::vector<float> model2 = ModelLoader::LoadOBJ("../../SKY/Game/RSC/ball.obj");
    std::vector<float> model3 = ModelLoader::LoadOBJ("../../SKY/Game/RSC/TeaPot.obj");


    Mesh mesh1(model1);  
    mesh1.Position = glm::vec3(5.0, -1.0, 0.0);
    mesh1.Scale = glm::vec3(1.2);

    Mesh mesh2(model2);  
    mesh2.Position = glm::vec3(2.5, 0.0, 0.0);
    mesh2.Scale = glm::vec3(0.7);

    Mesh mesh3(model3);  
    mesh3.Position = glm::vec3(2.0, -1.0, 2.5);
    mesh3.Scale = glm::vec3(0.5);


    glEnable(GL_DEPTH_TEST);
    while (!window.ShouldClose())
    {
        UpdateDeltaTime(window.GetTime());

        glClearColor(0.3f, 0.2f, 0.2f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        camera.UpdateMatrix();
        camera.KeyInput(shader);

        shader.Use();
        shader.setMat4("camMatrix", camera.camMatrix);
        mesh1.Draw(shader);
        mesh2.Draw(shader);
        mesh3.Draw(shader);

        	
        window.SwapBuffers();
        window.PollEvents();
    }

    return 0;
}