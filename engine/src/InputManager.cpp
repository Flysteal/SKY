#include "InputManager.h"
#include "GLFW/glfw3.h"
#include <iostream>

#include <unordered_map>

double p_xoffset, p_yoffset;

void ScrollCallback(GLFWwindow* window, double xoffset, double yoffset) 
{
    p_yoffset = -yoffset;
    p_xoffset = -xoffset;
}

InputManager::InputManager(GLFWwindow* window)
: k_window(window)
{
    glfwSetScrollCallback(k_window, ScrollCallback);
}

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


void InputManager::UpdateMousePosition()
{
    glfwGetCursorPos(k_window, &mouseX, &mouseY);

    if (firstMouse) {
        lastMouseX = mouseX;
        lastMouseY = mouseY;
        firstMouse = false;
    }

    deltaX = mouseX - lastMouseX;
    deltaY = lastMouseY - mouseY;  // Y is inverted in window coords

    lastMouseX = mouseX;
    lastMouseY = mouseY;
}

void InputManager::GetMousePosition(double& x, double& y) const
{
    x = mouseX;
    y = mouseY;
}

void InputManager::GetMouseDelta(double& dx, double& dy) const
{
    dx = deltaX;
    dy = deltaY;
}

void InputManager::MouseScroll(float& item, float sensitivity, bool isY)
{
    item += (isY ? p_xoffset : p_yoffset) * sensitivity;
    p_xoffset = 0.0;
    p_yoffset = 0.0;
}

void InputManager::ResetMousePos()
{
    firstMouse = true;
    glfwGetCursorPos(k_window, &lastMouseX, &lastMouseY);
    deltaX = 0.0;
    deltaY = 0.0;
}

void InputManager::CenterMouseCursor()
{
    int width, height;
    glfwGetWindowSize(k_window, &width, &height);
    glfwSetCursorPos(k_window, width / 2.0, height / 2.0);

    // Update internal state to avoid large jump next frame
    mouseX = width / 2.0;
    mouseY = height / 2.0;
    lastMouseX = mouseX;
    lastMouseY = mouseY;
    deltaX = 0.0;
    deltaY = 0.0;
}

void InputManager::ClearMousePos()
{
    firstMouse = true;
    glfwGetCursorPos(k_window, &lastMouseX, &lastMouseY);
    deltaX = 0.0;
    deltaY = 0.0;
    lastMouseX = 0.0;
    lastMouseY = 0.0;
    mouseX = 0.0;
    mouseY = 0.0;
}