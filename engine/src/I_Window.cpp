#include "Window.h"
#include "Camera.h"


#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"

#include "GLFW/glfw3.h"

bool vsync = true;

void Window::ImGuiUpdate() 
{
// Start new ImGui frame
ImGui_ImplOpenGL3_NewFrame();
ImGui_ImplGlfw_NewFrame();
ImGui::NewFrame();

   ImGui::Begin("Sky Lands-Debug");
    ImGui::Text("FPS: %.f", ImGui::GetIO().Framerate);
    ImGui::Text("ms/frame: %.2f", 1000.0f / ImGui::GetIO().Framerate); 

   ImGui::Spacing();

   // ImGui::Text("POS:", Position);

   ImGui::Spacing();

    if (ImGui::Checkbox("V-sync", &vsync)) 
    { glfwSwapInterval(vsync ? 1 : 0); }

   ImGui::End();


// Rendering
ImGui::Render();
ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void Window::ImGuiInit() 
{
    // Setup (once at init)
IMGUI_CHECKVERSION();
ImGui::CreateContext();
ImGuiIO& io = ImGui::GetIO(); (void)io;
// Setup ImGui style
ImGui::StyleColorsDark();

// Initialize ImGui GLFW + OpenGL3 bindings
ImGui_ImplGlfw_InitForOpenGL(m_Window, true);
ImGui_ImplOpenGL3_Init("#version 330 core");
}

void Window::ImGuiShutdown() 
{
  ImGui_ImplOpenGL3_Shutdown();
  ImGui_ImplGlfw_Shutdown();
  ImGui::DestroyContext();
}