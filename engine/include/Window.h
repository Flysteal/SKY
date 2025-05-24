#ifndef WINDOW_H
#define WINDOW_H

class GLFWwindow;

class Window 
{
public:

    Window(int width, int height, const char* title);;
	~Window();

    void PollEvents();
    void WaitEvents(float time);
    void SwapBuffers();
    bool ShouldClose();
    double GetTime();

    GLFWwindow* GetWindow();
private:
	GLFWwindow* m_Window;
};

#endif