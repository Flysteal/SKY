#include "InputManager.h"
#include "GLFW/glfw3.h"

#include <unordered_map>

InputManager::InputManager(GLFWwindow* window)
: k_window(window) {}

bool InputManager::IsKeyPressed(short int key)
{
	if(glfwGetKey(k_window, key) == GLFW_PRESS){
		return 1;
	}else{
		return 0;
	}
}

bool InputManager::IsKeyPressedOnce(short int key) {
    static std::unordered_map<int, bool> keyWasPressed;

    bool isPressed = glfwGetKey(k_window, key) == GLFW_PRESS;

    if (isPressed && !keyWasPressed[key]) {
        keyWasPressed[key] = true;
        return true;
    }

    if (!isPressed && keyWasPressed[key]) {
        keyWasPressed[key] = false;
    }

    return false; 
}

bool InputManager::IsKeyPressedToggle(short int key) {
    static std::unordered_map<int, bool> keyWasPressed;
    static std::unordered_map<int, bool> toggleState;

    bool isPressed = glfwGetKey(k_window, key) == GLFW_PRESS;

    if (isPressed && !keyWasPressed[key]) {
        keyWasPressed[key] = true;
        toggleState[key] = !toggleState[key]; 
    }

    if (!isPressed && keyWasPressed[key]) {
        keyWasPressed[key] = false;
    }

    return toggleState[key];
}

bool InputManager::IsMouseButtonPressed(short int key)
{
	if(glfwGetMouseButton(k_window, key) == GLFW_PRESS){
		return 1;
	}else{
		return 0;
	}
}

bool InputManager::IsMouseButtonPressedOnce(short int key)
{
    static std::unordered_map<int, bool> keyWasPressed;

    bool isPressed = glfwGetMouseButton(k_window, key) == GLFW_PRESS;

    if (isPressed && !keyWasPressed[key]) {
        keyWasPressed[key] = true;
        return true;
    }

    if (!isPressed && keyWasPressed[key]) {
        keyWasPressed[key] = false;
    }

    return false; 
}

bool InputManager::IsMouseButtonPressedToggle(short int key)
{
    static std::unordered_map<int, bool> keyWasPressed;
    static std::unordered_map<int, bool> toggleState;

    bool isPressed = glfwGetMouseButton(k_window, key) == GLFW_PRESS;

    if (isPressed && !keyWasPressed[key]) {
        keyWasPressed[key] = true;
        toggleState[key] = !toggleState[key]; 
    }

    if (!isPressed && keyWasPressed[key]) {
        keyWasPressed[key] = false;
    }

    return toggleState[key];
}
