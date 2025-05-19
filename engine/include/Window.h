#ifndef WINDOW_H
#define WINDOW_H

class GLFWwindow;

class Window 
{
public:

    Window(int width, int height, const char* title);;
	~Window();

    void PollEvents();
    void SwapBuffers();
    bool ShouldClose();
    double GetTime();


    GLFWwindow* GetWindow();
    bool Imgui;
private:
	GLFWwindow* m_Window;

    void ImGuiInit();
    void ImGuiUpdate();
    void ImGuiShutdown();
};

#endif