#include "window.h"


Window::Window(int width, int height, const char* name)
    : m_window(nullptr)
{

    if (!glfw_init()) {
        return ;
    }

    m_window = glfwCreateWindow(
        width,
        height,
        name,
        nullptr,
        nullptr
    );


    if (!m_window) {
        std::cerr << "Failed to create GLFW window\n";
        glfwTerminate();
        return;
    }

    glfwMakeContextCurrent(m_window);

    glfwSetFramebufferSizeCallback(
        m_window,
        framebuffer_size_callback
    );

    if (!gladLoadGLLoader(
        (GLADloadproc)glfwGetProcAddress
    )) {
        std::cerr << "Failed to initialize GLAD\n";
        return;
    }

    std::cout << "OpenGL initialized\n";
}



Window::~Window()
{
    if (m_window) {
        glfwDestroyWindow(m_window);
    }
    glfwTerminate();
}



bool Window::glfw_init()
{
    if (!glfwInit()) {
        std::cerr << "GLFW init failed\n";
        return false;
    }

    glfwWindowHint(
        GLFW_CONTEXT_VERSION_MAJOR,
        3
    );

    glfwWindowHint(
        GLFW_CONTEXT_VERSION_MINOR,
        3
    );

    glfwWindowHint(
        GLFW_OPENGL_PROFILE,
        GLFW_OPENGL_CORE_PROFILE
    );

    return true;
}

GLFWwindow* Window::get_window() const
{
    return m_window;
}

void Window::framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}