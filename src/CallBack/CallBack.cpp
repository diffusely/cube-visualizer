#include "CallBack.h"

namespace callback {

    double lastMouseX = 0;
    double lastMouseY = 0;

    float cubeRotX = 0.0f;
    float cubeRotY = 0.0f;

    bool mousePressed = false;

    void mouse_move_callback(GLFWwindow* window, double xpos, double ypos)
    {
        if (!mousePressed) {
            lastMouseX = xpos;
            lastMouseY = ypos;
            return;
        }

        float xoffset = xpos - lastMouseX;
        float yoffset = ypos - lastMouseY;

        lastMouseX = xpos;
        lastMouseY = ypos;

        float sensitivity = 0.3f;

        cubeRotY += xoffset * sensitivity;
        cubeRotX += yoffset * sensitivity;
    }

    void framebuffer_size_callback(GLFWwindow* window, int width, int height)
    {
        glViewport(0, 0, width, height);
    }

    void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
    {
        if (button == GLFW_MOUSE_BUTTON_LEFT) {
            mousePressed = (action == GLFW_PRESS);
        }
    }
}
