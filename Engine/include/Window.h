#ifndef WINDOW_H
#define WINDOW_H

#include <GLFW/glfw3.h>

class Window {
 public:
  Window(const char* title, int width, int height);
  ~Window();

  void PollEvents();
  void WaitEvents(float time);
  void SwapBuffers();
  bool ShouldClose();
  double GetTime();

  GLFWwindow* GetWindow();

 private:
  GLFWwindow* m_Window;  // main window
  void Delete();
};

#endif