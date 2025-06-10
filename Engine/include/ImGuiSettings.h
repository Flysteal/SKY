#ifndef IMGUI_SETTINGS_H
#define IMGUI_SETTINGS_H

struct GLFWwindow;
#include "glm/glm.hpp"


static float cords[12] ={
  0.0f, 1.0f, 1.0f,
  1.0f, 0.0f, 1.0f,
  1.0f, 1.0f, 0.0f,
  1.0f, 0.0f, 1.0f,
};
class ImGuiSettings {
public:
    ImGuiSettings(GLFWwindow* window);
    ~ImGuiSettings() = default;

    void Update();
    void Shutdown();

private:
    GLFWwindow* window;

};

#endif // IMGUI_SETTINGS_H
