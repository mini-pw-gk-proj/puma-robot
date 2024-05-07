//
// Created by faliszewskii on 10.01.24.
//

#include "InputHandler.h"
#include "imgui.h"

void InputHandler::setupCallbacks(GLFWwindow *window) {
    glfwSetWindowUserPointer(window, this);

    glfwSetKeyCallback(window, [](GLFWwindow *window, int key, int scancode, int action, int mods) {
        auto *inputHandler = static_cast<InputHandler *>(glfwGetWindowUserPointer(window));
        inputHandler->keyCallback(window, key, scancode, action, mods);
    });
    glfwSetCursorPosCallback(window, [](GLFWwindow *window, double xpos, double ypos) {
        auto *inputHandler = static_cast<InputHandler *>(glfwGetWindowUserPointer(window));
        inputHandler->mouseCallback(window, xpos, ypos);
    });
    glfwSetScrollCallback(window, [](GLFWwindow *window, double xoffset, double yoffset) {
        auto *inputHandler = static_cast<InputHandler *>(glfwGetWindowUserPointer(window));
        inputHandler->scrollCallback(window, xoffset, yoffset);
    });
    glfwSetMouseButtonCallback(window, [](GLFWwindow *window, int button, int action, int mods) {
        auto *inputHandler = static_cast<InputHandler *>(glfwGetWindowUserPointer(window));
        inputHandler->mouseButtonCallback(window, button, action, mods);
    });
    glfwSetWindowSizeCallback(window, [](GLFWwindow *window, int width, int height) {
        auto *inputHandler = static_cast<InputHandler *>(glfwGetWindowUserPointer(window));
        inputHandler->windowResize(window, width, height);
    });
}


void InputHandler::keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods) const {
    static auto deltaTime = static_cast<float>(glfwGetTime());
    deltaTime = static_cast<float>(glfwGetTime()) - deltaTime;

    // TODO: Reimplement handling of input to use imGUI
    //if (ImGui::GetIO().WantCaptureMouse) return;
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    if (key == GLFW_KEY_W && action == GLFW_PRESS && appContext.cameraType == CameraType::FREEANCHOR)
        appContext.camera->processKeyboard(FORWARD, deltaTime);
    if (key == GLFW_KEY_S && action == GLFW_PRESS && appContext.cameraType == CameraType::FREEANCHOR)
        appContext.camera->processKeyboard(BACKWARD, deltaTime);
    if (key == GLFW_KEY_A && action == GLFW_PRESS && appContext.cameraType == CameraType::FREEANCHOR)
        appContext.camera->processKeyboard(LEFT, deltaTime);
    if (key == GLFW_KEY_D && action == GLFW_PRESS && appContext.cameraType == CameraType::FREEANCHOR)
        appContext.camera->processKeyboard(RIGHT, deltaTime);
}

void InputHandler::mouseButtonCallback(GLFWwindow *window, int button, int action, int mods) {
    if(appContext.cameraType == CameraType::FREEANCHOR)
    {
        if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS)
            appContext.guiFocus = false;
        else
        {
            appContext.guiFocus = true;
        }
    }
}

// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void InputHandler::mouseCallback(GLFWwindow *window, double xposIn, double yposIn) {
    if(appContext.cameraType == CameraType::FREEANCHOR)
    {
        auto xpos = static_cast<float>(xposIn);
        auto ypos = static_cast<float>(yposIn);

        static float lastX = xpos;
        static float lastY = ypos;
        static bool firstMouse = true;

        if (firstMouse)
        {
            lastX = xpos;
            lastY = ypos;
            firstMouse = false;
        }

        float xoffset = xpos - lastX;
        float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

        lastX = xpos;
        lastY = ypos;

        if (!appContext.guiFocus)
        {

            appContext.camera->processMouseMovement(xoffset, yoffset);
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        }
        else glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    }
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void InputHandler::scrollCallback(GLFWwindow *window, double xoffset, double yoffset) {
    // TODO: Reimplement handling of input to use imGUI
    //if (ImGui::GetIO().WantCaptureMouse) return;
    if(appContext.cameraType == CameraType::FREEANCHOR)
    {
        appContext.camera->processMouseScroll(static_cast<float>(yoffset));
    }
}

void InputHandler::windowResize (GLFWwindow *window, int width, int height)
{
    appContext.glfw_window_resize(width, height);
}
