#ifndef IMGUI_SETTINGS_H
#define IMGUI_SETTINGS_H

struct GLFWwindow;

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
