#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace callback {

    extern float cameraDistance;
    extern double lastMouseX;
    extern double lastMouseY;
    extern float cubeRotX;
    extern float cubeRotY;
    extern bool mousePressed;

    void mouse_move_callback(GLFWwindow* window, double xpos, double ypos);
    void framebuffer_size_callback(GLFWwindow* window, int width, int height);
    void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
    void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

}