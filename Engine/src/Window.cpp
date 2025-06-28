#include <glad/gl.h>
#include "Window.h"

// #include <GLFW/glfw3.h>

#include <iostream>

Window::Window(const char* title, int width, int height) {
  if (!glfwInit()) {
    glfwTerminate();
    std::cerr << "Failed to initialize GLFW";
  }
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  m_Window = glfwCreateWindow(width, height, title, nullptr, nullptr);
  glfwMakeContextCurrent(m_Window);

  if (!gladLoadGL((GLADloadfunc)glfwGetProcAddress)) {
    glfwDestroyWindow(m_Window);
    glfwTerminate();
    std::cerr << ("Failed to initialize GLAD\n");
  }
}

Window::~Window() { Delete(); }

void Window::PollEvents() { glfwPollEvents(); }

void Window::WaitEvents(float time) { glfwWaitEventsTimeout(time); }

void Window::SwapBuffers() { glfwSwapBuffers(m_Window); }

bool Window::ShouldClose() { return glfwWindowShouldClose(m_Window); }

GLFWwindow* Window::GetWindow() { return m_Window; }

double Window::GetTime() { return glfwGetTime(); }

void Window::Delete() {
  glfwDestroyWindow(m_Window);
  glfwTerminate();
}