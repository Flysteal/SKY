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
};
glm::vec3 cubePositions[] = {
    glm::vec3( 0.0f,  0.0f,  0.0f),
    glm::vec3( 2.0f,  5.0f, -15.0f),
    glm::vec3(-1.5f, -2.2f, -2.5f),
    glm::vec3(-3.8f, -2.0f, -12.3f),
    glm::vec3( 2.4f, -0.4f, -3.5f),
    glm::vec3(-1.7f,  3.0f, -7.5f),
    glm::vec3( 1.3f, -2.0f, -2.5f),
    glm::vec3( 1.5f,  2.0f, -2.5f),
    glm::vec3( 1.5f,  0.2f, -1.5f),
    glm::vec3(-1.3f,  1.0f, -1.5f)
};
glm::vec3 pointLightPositions[] = {
    glm::vec3( 0.7f,  0.2f,  2.0f),
    glm::vec3( 2.3f, -3.3f, -4.0f),
    glm::vec3(-4.0f,  2.0f, -12.0f),
    glm::vec3( 0.0f,  0.0f, -3.0f)
};
glm::vec3 pointLightColors[] = {
    glm::vec3(0.2f, 0.2f, 0.6f),
    glm::vec3(0.3f, 0.3f, 0.7f),
    glm::vec3(0.0f, 0.0f, 0.3f),
    glm::vec3(0.4f, 0.4f, 0.4f)
};

int main() {
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
// 

    Texture tex1, tex1S;
    shader.Activate();
    tex1.Init("../../SKY/game/Resources/brick.jpg", GL_TEXTURE_2D, GL_TEXTURE0, GL_UNSIGNED_BYTE);
    tex1.texUnit(shader, "tex0", 0);
    tex1S.Init("../../SKY/game/Resources/brick_specular.jpg", GL_TEXTURE_2D, GL_TEXTURE1, GL_UNSIGNED_BYTE);
    tex1S.texUnit(shader, "tex0", 0);

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

    while (!window.ShouldClose())
    {
        updateDeltaTime();
        glClearColor(0.1f, 0.1f, 0.2f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

        camera.UpdateMatrix();
        camera.KeyInput(shader);
        
        //
        shader.Activate();

        // Material properties
        shader.setInt("material.diffuse", 0);
        shader.setInt("material.specular", 1);
        shader.setFloat("material.shininess", 32.0f);

        for (unsigned int i = 0; i < 10; i++)
        {
            camera.Matrix(shader, "camMatrix"); // sets view * projection matrix uniform "camMatrix"
            glm::mat4 model1 = glm::mat4(1.0f);
            model1 = glm::translate(model1, cubePositions[i]);
            float angle = 20.0f * i;
            model1 = glm::rotate(model1, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
            shader.setMat4("model", model1);

            tex1.Bind();
            tex1S.Bind();
            VAO1.Bind();
            glDrawElements(GL_TRIANGLES, sizeof(indices1) / sizeof(unsigned int), GL_UNSIGNED_INT, 0);
        }
        // View position
        shader.setVec3("viewPos", camera.Position.x, camera.Position.y, camera.Position.z);

// {
        // Directional light
        shader.setVec3("dirLight.direction", -0.2f, -1.0f, -0.3f);      
        shader.setVec3("dirLight.ambient", 0.05f, 0.05f, 0.1f); 
        shader.setVec3( "dirLight.diffuse", 0.2f, 0.2f, 0.7); 
        shader.setVec3( "dirLight.specular", 0.7f, 0.7f, 0.7f);
        // Point light 1
        shader.setVec3("pointLights[0].position", pointLightPositions[0].x, pointLightPositions[0].y, pointLightPositions[0].z);        
        shader.setVec3("pointLights[0].ambient", pointLightColors[0].x * 0.1,  pointLightColors[0].y * 0.1,  pointLightColors[0].z * 0.1);      
        shader.setVec3("pointLights[0].diffuse", pointLightColors[0].x,  pointLightColors[0].y,  pointLightColors[0].z); 
        shader.setVec3("pointLights[0].specular", pointLightColors[0].x,  pointLightColors[0].y,  pointLightColors[0].z);
        shader.setFloat("pointLights[0].constant", 1.0f);
        shader.setFloat("pointLights[0].linear", 0.09);
        shader.setFloat("pointLights[0].quadratic", 0.032);     
        // Point light 2
        shader.setVec3("pointLights[1].position", pointLightPositions[1].x, pointLightPositions[1].y, pointLightPositions[1].z);        
        shader.setVec3("pointLights[1].ambient", pointLightColors[1].x * 0.1,  pointLightColors[1].y * 0.1,  pointLightColors[1].z * 0.1);      
        shader.setVec3("pointLights[1].diffuse", pointLightColors[1].x,  pointLightColors[1].y,  pointLightColors[1].z); 
        shader.setVec3("pointLights[1].specular", pointLightColors[1].x,  pointLightColors[1].y,  pointLightColors[1].z);
        shader.setFloat("pointLights[1].constant", 1.0f);
        shader.setFloat("pointLights[1].linear", 0.09);
        shader.setFloat("pointLights[1].quadratic", 0.032);     
        // Point light 3
        shader.setVec3("pointLights[2].position", pointLightPositions[2].x, pointLightPositions[2].y, pointLightPositions[2].z);        
        shader.setVec3("pointLights[2].ambient", pointLightColors[2].x * 0.1,  pointLightColors[2].y * 0.1,  pointLightColors[2].z * 0.1);      
        shader.setVec3("pointLights[2].diffuse", pointLightColors[2].x,  pointLightColors[2].y,  pointLightColors[2].z); 
        shader.setVec3("pointLights[2].specular", pointLightColors[2].x,  pointLightColors[2].y,  pointLightColors[2].z);
        shader.setFloat("pointLights[2].constant", 1.0f);
        shader.setFloat("pointLights[2].linear", 0.09);
        shader.setFloat("pointLights[2].quadratic", 0.032);     
        // Point light 4
        shader.setVec3("pointLights[3].position", pointLightPositions[3].x, pointLightPositions[3].y, pointLightPositions[3].z);        
        shader.setVec3("pointLights[3].ambient", pointLightColors[3].x * 0.1,  pointLightColors[3].y * 0.1,  pointLightColors[3].z * 0.1);      
        shader.setVec3("pointLights[3].diffuse", pointLightColors[3].x,  pointLightColors[3].y,  pointLightColors[3].z); 
        shader.setVec3("pointLights[3].specular", pointLightColors[3].x,  pointLightColors[3].y,  pointLightColors[3].z);
        shader.setFloat("pointLights[3].constant", 1.0f);
        shader.setFloat("pointLights[3].linear", 0.09);
        shader.setFloat("pointLights[3].quadratic", 0.032);     
        // SpotLight
        shader.setVec3("spotLight.position", camera.Position.x, camera.Position.y, camera.Position.z);  
        shader.setVec3("spotLight.direction", camera.Orientation.x, camera.Orientation.y, camera.Orientation.z);
        shader.setVec3("spotLight.ambient", 0.0f, 0.0f, 0.0f);  
        shader.setVec3("spotLight.diffuse", 1.0f, 1.0f, 1.0f); 
        shader.setVec3("spotLight.specular", 1.0f, 1.0f, 1.0f);
        shader.setFloat("spotLight.constant", 1.0f);
        shader.setFloat("spotLight.linear", 0.009);
        shader.setFloat("spotLight.quadratic", 0.0032);         
        shader.setFloat("spotLight.cutOff", glm::cos(glm::radians(10.0f)));
        shader.setFloat("spotLight.outerCutOff", glm::cos(glm::radians(12.5f)));
// }

        // LIGHT CUBES
        for(int i = 0; i < 4; i++) {
            glm::mat4 model2 = glm::mat4(1.0f);
            model2 = glm::translate(model2, pointLightPositions[i]);
            lightShader.Activate();
            camera.Matrix(lightShader, "camMatrix");
            lightShader.setMat4("model", model2);
            lightShader.setVec3("color", pointLightColors[i]);
            VAO2.Bind();
            glDrawElements(GL_TRIANGLES, sizeof(indices2) / sizeof(unsigned int), GL_UNSIGNED_INT, 0);
        }

        IMGUI.Update();
        window.SwapBuffers();
        // window.WaitEvents(0.01);
        window.PollEvents();
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