#ifndef IMGUI_SETTINGS_H
#define IMGUI_SETTINGS_H

struct GLFWwindow;

class ImGuiSettings{
public:
    ImGuiSettings(GLFWwindow* window);

    void Update();
    void Shutdown();

private:
    GLFWwindow* window;

};

#endif