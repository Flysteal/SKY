#include <glad/gl.h>
#include "Window.h"
#include <GLFW/glfw3.h>
#include <stdexcept>

#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"



Window::Window(int width, int height, const char* title){
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    m_Window = glfwCreateWindow(width, height, title, nullptr, nullptr);
    glfwMakeContextCurrent(m_Window);

    if (!gladLoadGL((GLADloadfunc)glfwGetProcAddress)){
        glfwDestroyWindow(m_Window);
        glfwTerminate();
        throw std::runtime_error("Failed to initialize GLAD");
    }

    if (Imgui){ ImGuiInit(); };

}


Window::~Window() {
    if (Imgui){ ImGuiShutdown(); };
    glfwDestroyWindow(m_Window);
    glfwTerminate();
}

void Window::PollEvents()  {
    glfwPollEvents();
}

void Window::SwapBuffers()  {
    if (Imgui){ ImGuiUpdate(); };
    glfwSwapBuffers(m_Window);

}

bool Window::ShouldClose()  {
    return glfwWindowShouldClose(m_Window);
}

GLFWwindow* Window::GetWindow()  {
    return m_Window;
}

double GetTime() { return glfwGetTime(); }


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