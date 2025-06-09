#ifndef WINDOW_H
#define WINDOW_H

class GLFWwindow;

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