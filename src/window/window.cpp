#include "Window.h"

Window::Window(int width, int height, const char* name)
    : m_Window(nullptr)
    , m_Width(width)
    , m_Height(height)
{

    if (!GlfwInit())
        return ;
  
    m_Window = glfwCreateWindow(width, height, name, NULL, NULL);

    if (!m_Window) {
        std::cerr << "Failed to create GLFW window\n";
        glfwTerminate();
        return;
    }

    glfwMakeContextCurrent(m_Window);
    glfwSetFramebufferSizeCallback(m_Window, callback::framebuffer_size_callback);
    glfwSetCursorPosCallback(m_Window, callback::mouse_move_callback);
    glfwSetMouseButtonCallback(m_Window, callback::mouse_button_callback);


    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD\n";
        return;
    }

    std::cout << "OpenGL initialized\n";
}

Window::~Window()
{
    if (m_Window) {
        glfwDestroyWindow(m_Window);
    }
    glfwTerminate();
}

void Window::Clear()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Window::Update()
{
    glfwSwapBuffers(m_Window);
    glfwPollEvents();
}

bool Window::ShouldClose() const
{
    return glfwWindowShouldClose(m_Window);
}

bool Window::GlfwInit()
{
    if (!glfwInit()) {
        std::cerr << "GLFW init failed\n";
        return false;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    return true;
}

GLFWwindow* Window::GetNativeWindow() const
{
    return m_Window;
}
