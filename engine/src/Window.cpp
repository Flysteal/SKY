#include <glad/gl.h>
#include "Window.h"
#include <GLFW/glfw3.h>
// #include <stdexcept>
#include <iostream>


Window::Window(int width, int height, const char* title){
    if(!glfwInit())
    {
        glfwTerminate();
        throw std::runtime_error("Failed to initialize GLFW");
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    m_Window = glfwCreateWindow(width, height, title, nullptr, nullptr);
    glfwMakeContextCurrent(m_Window);

    if (!gladLoadGL((GLADloadfunc)glfwGetProcAddress)){
        glfwDestroyWindow(m_Window);
        glfwTerminate();
        std::cerr << ("Failed to initialize GLAD\n");
    }
}


Window::~Window() {
    glfwDestroyWindow(m_Window);
    glfwTerminate();
}

void Window::PollEvents()  {
    glfwPollEvents();
}

void Window::WaitEvents(float time)  {
glfwWaitEventsTimeout(time);
}

void Window::SwapBuffers()  {
    glfwSwapBuffers(m_Window);

}

bool Window::ShouldClose()  {
    return glfwWindowShouldClose(m_Window);
}

GLFWwindow* Window::GetWindow()  {
    return m_Window;
}

double GetTime() { return glfwGetTime(); }