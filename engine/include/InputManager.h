#ifndef INPUT_MANAGER_H
#define INPUT_MANAGER_H

// #include "GLFW/glfw3.h"
struct GLFWwindow;

class InputManager {
public:
	InputManager(GLFWwindow* window);
	// ~InputManager();

	bool IsKeyPressed(short int key);
	bool IsKeyPressedOnce(short int key);
	bool IsKeyPressedToggle(short int key);

	bool IsMouseButtonPressed(short int key);
	bool IsMouseButtonPressedOnce(short int key);
	bool IsMouseButtonPressedToggle(short int key); 

    void UpdateMousePosition();
    void GetMousePosition(double& x, double& y) const;
    void GetMouseDelta(double& dx, double& dy) const;
    void MouseScroll(float& item, float sensitivity, bool isY);

    void ResetMousePos();
    void ClearMousePos();

    void CenterMouseCursor();

	GLFWwindow* k_window;

private:

    double lastMouseX = 0.0;
    double lastMouseY = 0.0;
    double mouseX = 0.0;
    double mouseY = 0.0;
    double deltaX = 0.0;
    double deltaY = 0.0;


    bool firstMouse = true;  // To initialize lastMouseX/Y on first frame
};

#endif
