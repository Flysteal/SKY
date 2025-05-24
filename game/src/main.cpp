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
#include "glm/vec4.hpp"

int height = 800;
int width = 800;

Camera* Gptr_camera = nullptr;

void window_size_callback(GLFWwindow* window, int width, int height);

float vertices[] =
{ //     COORDINATES     /        COLORS      /   TexCoord  //
    -0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,    0.0f, 0.0f,
    -0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,    5.0f, 0.0f,
     0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,    0.0f, 0.0f,
     0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,    5.0f, 0.0f,
     0.0f, 0.8f,  0.0f,     0.92f, 0.86f, 0.76f,    2.5f, 5.0f
};

unsigned int indices[] =
{
    0, 1, 2,
    0, 2, 3,
    0, 1, 4,
    1, 2, 4,
    2, 3, 4,
    3, 0, 4
};
float  vertices2[] = {
    //cord
    -0.1f, -0.1f,  0.1f,
    -0.1f, -0.1f, -0.1f,
     0.1f, -0.1f, -0.1f,
     0.1f, -0.1f,  0.1f,
    -0.1f,  0.1f,  0.1f,
    -0.1f,  0.1f, -0.1f,
     0.1f,  0.1f, -0.1f,
     0.1f,  0.1f,  0.1f
};
unsigned int indices2[]= {
    0, 1, 2,
    0, 2, 3,
    0, 4, 7,
    0, 7, 3,
    3, 7, 6,
    3, 6, 2,
    2, 6, 5,
    2, 5, 1,
    1, 5, 4,
    1, 4, 0,
    4, 5, 6,
    4, 6, 7
};

int main() {


    std::cout << "directory: " << std::filesystem::current_path() << "\n";
// {
    Window window(height, width, "SkyLands");
    ImGuiSettings IMGUI(window.GetWindow());

    Shader shader;
    shader.LoadShaders("../../SKY/game/Shaders/glm.vert", "../../SKY/game/Shaders/glm.frag");

    Camera camera(window.GetWindow(),  height, width);
    Gptr_camera = &camera;
// }

    glfwSetWindowSizeCallback(window.GetWindow(), window_size_callback);

// {
    //
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

    // Texture tex2;
    // tex2.Init("../../SKY/game/Resources/icon.png", GL_TEXTURE_2D, GL_TEXTURE1, GL_UNSIGNED_BYTE);
    // tex2.texUnit(shader, "tex1", 1);

    VAO1.Unbind();
    VBO1.Unbind();
    EBO1.Unbind();
//
    Shader lightShader;
    lightShader.LoadShaders("../../SKY/game/Shaders/default.vert", "../../SKY/game/Shaders/default.frag");
    VAO VAO2;
    VAO2.Bind();

    VBO VBO2(vertices2, sizeof(vertices2));
    EBO EBO2(indices2, sizeof(indices2));

    VAO2.LinkAttrib(VBO2, 0, 3, GL_FLOAT, 3 * sizeof(float), (void*)0);

    VAO2.Unbind();
    VBO2.Unbind();
    EBO2.Unbind();
    glm::vec4 lightColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);


// }
    glEnable(GL_DEPTH_TEST);


    while (!window.ShouldClose())
    {
        updateDeltaTime();
        glClearColor(0.1f, 0.1f, 0.2f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

        camera.UpdateMatrix();
        camera.KeyInput(shader);
        
        shader.Activate();
        camera.Matrix(shader, "camMatrix");

        tex1.Bind();
        // tex2.Bind();
        VAO1.Bind();

        glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(int), GL_UNSIGNED_INT, 0);


        lightShader.Activate();
        camera.Matrix(lightShader, "camMatrix");

        VAO2.Bind();

        glDrawElements(GL_TRIANGLES, sizeof(indices2) / sizeof(int), GL_UNSIGNED_INT, 0);


        IMGUI.Update();
        window.SwapBuffers();
        window.PollEvents();
    }


    IMGUI.Shutdown();
    tex1.Delete();
    // tex2.Delete();
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