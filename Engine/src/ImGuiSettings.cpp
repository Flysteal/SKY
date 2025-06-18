#include "ImGuiSettings.h"

#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"
#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "imgui.h"

#include "Camera.h"
#include "GLFW/glfw3.h"

bool vsync = true;


float cords[] = {12.0f, 8.0f, 0.0f,  1.0f, 5.0f, 14.0f,
                 12.0f, 8.0f, 15.0f, 0.0f, 0.0f, 0.0f};

ImGuiSettings::ImGuiSettings(GLFWwindow *window) : window(window) {
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    (void)io;
    // Setup ImGui style
    ImGui::StyleColorsDark();

    // Initialize ImGui GLFW + OpenGL3 bindings
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 420 core");
}

void ImGuiSettings::Update() {
    // Start new ImGui frame
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

  ImGui::Begin("Sky Lands-Debug");

    ImGui::Text("FPS: %.f", ImGui::GetIO().Framerate);
    ImGui::Text("ms/frame: %.2f", 1000.0f / ImGui::GetIO().Framerate);

    ImGui::Spacing();

    if (ImGui::Checkbox("V-sync", &vsync))
    {
        glfwSwapInterval(vsync ? 1 : 0);
    }

    ImGui::Spacing();



    static bool faceCullingEnabled = false;
    static bool cullFront = false;
    static bool useCCW = false; // false = CW, true = CCW


    ImGui::SeparatorText("Face Culling");
    ImGui::Checkbox("Enable Face Culling", &faceCullingEnabled);
    ImGui::Checkbox("Cull Front Faces (instead of Back)", &cullFront);
    ImGui::Checkbox("Use CCW Front Faces (instead of CW)", &useCCW);

    if (faceCullingEnabled)
    {
        glEnable(GL_CULL_FACE);
        glCullFace(cullFront ? GL_FRONT : GL_BACK);
        glFrontFace(useCCW ? GL_CCW : GL_CW);
    }
    else
    {
        glDisable(GL_CULL_FACE);
    }




  ImGui::End();

  ImGui::Begin("Coordinates");

    ImGui::InputFloat3("float1", &cords[0]);
    ImGui::InputFloat3("float2", &cords[3]);
    ImGui::InputFloat3("float3", &cords[6]);
    ImGui::InputFloat3("float4", &cords[9]);

  ImGui::End();

    // Rendering
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void ImGuiSettings::Shutdown() {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}