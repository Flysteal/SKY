#include "VBO.h"
#include "VAO.h"
#include "EBO.h"
#include "Texture.h"
#include "Camera.h"
#include "Shader.h"

#include "Window.h"

#include <iostream>
#include <filesystem>

#include "DeltaTime.h"

#include "GLFW/glfw3.h"
#include "ImGuiSettings.h"

int height = 800;
int width = 800;

Camera* Gptr_camera = nullptr;

void window_size_callback(GLFWwindow* window, int width, int height);

float vertices[] = {
//cord   X     Y     Z color R     G     B tcord S     T
    -0.5f,  0.5f, 0.0f,     1.0f, 0.0f, 0.0f,   0.0f, 0.0f,// u left
     0.5f,  0.5f, 0.0f,     0.0f, 1.0f, 0.0f,   1.0f, 0.0f,// u right
     0.5f, -0.5f, 0.0f,     0.0f, 0.0f, 1.0f,   1.0f, 1.0f,// b right
    -0.5f, -0.5f, 0.0f,     1.0f, 1.0f, 0.0f,   0.0f, 1.0f// b left
}; 
unsigned int indices[] = { // start from 0
    0, 1, 2, 
    0, 3, 2 
};  

int main() {


    std::cout << "directory: " << std::filesystem::current_path() << "\n";
// {
    Window window(height, width, "SkyLands");
    ImGuiSettings IMGUI(window.GetWindow());

    Shader shader;
    shader.LoadShaders("../../SKY/game/Shaders/glm.vert", "../../SKY/game/Shaders/glm.frag");

    Camera camera(window.GetWindow(), shader, height, width);
    Gptr_camera = &camera;
// }

    glfwSetWindowSizeCallback(window.GetWindow(), window_size_callback);


// {
    VAO VAO1;
    VAO1.Bind();
    
    VBO VBO1(vertices, sizeof(vertices));
    EBO EBO1(indices, sizeof(indices));

    VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
    VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    VAO1.LinkAttrib(VBO1, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));

    Texture tex1;
    tex1.Init("../../SKY/game/Resources/brick.jpg", GL_TEXTURE_2D, GL_TEXTURE0, GL_UNSIGNED_BYTE);
    tex1.texUnit(shader, "tex0", 0);

    Texture tex2;
    tex2.Init("../../SKY/game/Resources/icon.png", GL_TEXTURE_2D, GL_TEXTURE1, GL_UNSIGNED_BYTE);
    tex2.texUnit(shader, "tex1", 1);

    VAO1.Unbind();
    VBO1.Unbind();
    EBO1.Unbind();

// }

    while (!window.ShouldClose())
    {
        updateDeltaTime();
        glClearColor(0.1f, 0.1f, 0.2f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

        shader.Activate();
        camera.KeyInput();
        
        camera.Matrix("camMatrix");


        tex1.Bind();
        tex2.Bind();
        VAO1.Bind();

        glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(int), GL_UNSIGNED_INT, 0);

        IMGUI.Update();
        window.SwapBuffers();
        window.PollEvents();
    }


    IMGUI.Shutdown();
    tex1.Delete();
    tex2.Delete();
    VAO1.Delete();
    VBO1.Delete();
    EBO1.Delete();
    shader.Delete();
    return 0;
}

void window_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
    
    if (Gptr_camera)
    {
        Gptr_camera->UpdateResolution(width, height);
    }
    std::cout << "Resized to: " << width << " x " << height << "\n";
}