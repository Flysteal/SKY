#include "VBO.h"
#include "VAO.h"
#include "EBO.h"
#include "Texture.h"
#include "Camera.h"
#include "Shader.h"
#include "Window.h"
#include "DeltaTime.h"
#include "ImGuiSettings.h"

#include <iostream>
#include <filesystem>
#include "GLFW/glfw3.h"

#include "glm/vec4.hpp"
#include <glm/gtc/matrix_transform.hpp>

int height = 800;
int width = 800;

Camera* Gptr_camera = nullptr;

void window_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
    
    if (Gptr_camera)
    {
        Gptr_camera->UpdateResolution(width, height);
    }
}

float vertices1[] =
{ //  position         / normal           /  texCoord  //
    // Front face
    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f, 0.0f, // bottom-left
     0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f, 0.0f, // bottom-right
     0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f, 1.0f, // top-right
    -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f, 1.0f, // top-left

    // Back face
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f, // bottom-right
     0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f, // bottom-left
     0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f, // top-left
    -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f, // top-right

    // Left face
    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f, // top-right
    -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f, // top-left
    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f, // bottom-left
    -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f, // bottom-right

    // Right face
     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f, // top-left
     0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f, // top-right
     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f, // bottom-right
     0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f, // bottom-left

    // Top face
    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f, // top-left
     0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 1.0f, // top-right
     0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f, // bottom-right
    -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f, // bottom-left

    // Bottom face
    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f, // top-right
     0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f, // top-left
     0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f, // bottom-left
    -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f  // bottom-right
};


unsigned int indices1[] = {
    0,  1,  2,  0,  2,  3,    // Front face
    4,  5,  6,  4,  6,  7,    // Back face
    8,  9, 10,  8, 10, 11,    // Left face
    12, 13, 14, 12, 14, 15,   // Right face
    16, 17, 18, 16, 18, 19,   // Top face
    20, 21, 22, 20, 22, 23    // Bottom face
};


float vertices2[] = {
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
    0, 1, 2, 0, 2, 3,
    0, 4, 7, 0, 7, 3,
    3, 7, 6, 3, 6, 2,
    2, 6, 5, 2, 5, 1,
    1, 5, 4, 1, 4, 0,
    4, 5, 6, 4, 6, 7
};;

int main() {
    std::cout << "directory: " << std::filesystem::current_path() << "\n";
// {
    Window window(height, width, "SkyLands");
    ImGuiSettings IMGUI(window.GetWindow());

    glfwSetWindowSizeCallback(window.GetWindow(), window_size_callback);
// 
    Shader shader;
    shader.LoadShaders("../../SKY/game/Shaders/default.vert", "../../SKY/game/Shaders/default.frag");

    Shader lightShader;
    lightShader.LoadShaders("../../SKY/game/Shaders/light.vert", "../../SKY/game/Shaders/light.frag");

    Camera camera(window.GetWindow(),  height, width);
    Gptr_camera = &camera;
// }
// {
    VAO VAO1;
    VAO1.Bind();
    
    VBO VBO1(vertices1, sizeof(vertices1));
    EBO EBO1(indices1, sizeof(indices1));

    VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);                // position
    VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float))); // normal
    VAO1.LinkAttrib(VBO1, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float))); // texcoords


    Texture tex1;
    tex1.Init("../../SKY/game/Resources/brick.jpg", GL_TEXTURE_2D, GL_TEXTURE0, GL_UNSIGNED_BYTE);
    tex1.texUnit(shader, "tex0", 0);
    VAO1.Unbind();
//
    VAO VAO2;
    VAO2.Bind();

    VBO VBO2(vertices2, sizeof(vertices2));
    EBO EBO2(indices2, sizeof(indices2));

    VAO2.LinkAttrib(VBO2, 0, 3, GL_FLOAT, 3 * sizeof(float), (void*)0);
    VAO2.Unbind();
// }
    glEnable(GL_DEPTH_TEST);

    glm::vec3 lightPos = glm::vec3(1.0f, 1.0f, 1.0f);

    while (!window.ShouldClose())
    {
        updateDeltaTime();
        glClearColor(0.1f, 0.1f, 0.2f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

        camera.UpdateMatrix();
        camera.KeyInput(shader);
        
        //
        glm::mat4 model1 = glm::mat4(1.0f);
        shader.Activate();
        camera.Matrix(shader, "camMatrix");
        shader.SetMat4("model", model1);
        shader.setVec3("lightColor", 1.0f, 1.0f, 1.0f );
        shader.setVec3("lightPos", lightPos);
        shader.setVec3("objectColor", 1.0f, 0.5f, 0.31f );
        tex1.Bind();
        VAO1.Bind();
        glDrawElements(GL_TRIANGLES, sizeof(indices1) / sizeof(int), GL_UNSIGNED_INT, 0);

        // 
        glm::mat4 model2 = glm::mat4(1.0f);
        model2 = glm::translate(model2, lightPos); // move 2 units on X
        lightShader.Activate();

        camera.Matrix(lightShader, "camMatrix");

        lightShader.SetMat4("model", model2);
        VAO2.Bind();
        glDrawElements(GL_TRIANGLES, sizeof(indices2) / sizeof(int), GL_UNSIGNED_INT, 0);



        IMGUI.Update();
        window.SwapBuffers();
        window.WaitEvents(0.01);
        // window.PollEvents();
    }


    IMGUI.Shutdown();
    tex1.Delete();
    VAO1.Delete();
    VAO2.Delete();
    VBO1.Delete();
    VBO2.Delete();
    EBO1.Delete();
    EBO2.Delete();
    shader.Delete();
    lightShader.Delete();
    return 0;
}

