#ifndef INPUT_MANAGER_H
#define INPUT_MANAGER_H

#include "GLFW/glfw3.h"


class InputManager {
public:
	InputManager(GLFWwindow* window);
	// ~InputManager();

	bool IsKeyPressed(short int key);
	bool IsKeyPressedOnce(short int key);
	bool IsKeyPressedToggle(short int key);

	bool IsMouseButtonPressed(short int key);
	bool IsMouseButtonPressdOnce(short int key);
	bool IsMouseButtonPressedToggle(short int key); 

	// void MousePos();

private:	
	GLFWwindow* k_window;
};

#endif
