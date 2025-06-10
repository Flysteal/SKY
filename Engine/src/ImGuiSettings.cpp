#include "ImGuiSettings.h"

#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"
#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "GLFW/glfw3.h"
#include "Camera.h"

bool vsync = true;



ImGuiSettings::ImGuiSettings(GLFWwindow* window)
: window(window)
{
IMGUI_CHECKVERSION();
ImGui::CreateContext();
ImGuiIO& io = ImGui::GetIO(); (void)io;
// Setup ImGui style
ImGui::StyleColorsDark();

// Initialize ImGui GLFW + OpenGL3 bindings
ImGui_ImplGlfw_InitForOpenGL(window, true);
ImGui_ImplOpenGL3_Init("#version 420 core");
}

void ImGuiSettings::Update() 
{
// Start new ImGui frame
ImGui_ImplOpenGL3_NewFrame();
ImGui_ImplGlfw_NewFrame();
ImGui::NewFrame();

   ImGui::Begin("Sky Lands-Debug");
    ImGui::Text("FPS: %.f", ImGui::GetIO().Framerate);
    ImGui::Text("ms/frame: %.2f", 1000.0f / ImGui::GetIO().Framerate); 

   ImGui::Spacing();

   // ImGui::Text("POS:", );

   ImGui::Spacing();

    if (ImGui::Checkbox("V-sync", &vsync)) 
    { glfwSwapInterval(vsync ? 1 : 0); }

   ImGui::End();
    ImGui::Begin("Coordinates");
    ImGui::InputFloat3("float1", &cords[3]);
    ImGui::InputFloat3("float2", &cords[6]);
    ImGui::InputFloat3("float3", &cords[9]);
    ImGui::InputFloat3("float4", &cords[12]);

    ImGui::End();

// Rendering
ImGui::Render();
ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void ImGuiSettings::Shutdown() 
{
  ImGui_ImplOpenGL3_Shutdown();
  ImGui_ImplGlfw_Shutdown();
  ImGui::DestroyContext();
}