#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "graphics/Shader/Shader.h"
#include "graphics/VertexArray/VertexArray.h"
#include "graphics/VertexBuffer/VertexBuffer.h"
#include "graphics/IndexBuffer/IndexBuffer.h"

int main() {
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW!" << std::endl;
        return -1;
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    GLFWwindow* window = glfwCreateWindow(800, 600, "OpenGL Square", nullptr, nullptr);
    if (!window) {
        std::cerr << "Failed to create GLFW window!" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD!" << std::endl;
        return -1;
    }

    float vertices[] = {
        -0.5f, -0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
         0.5f,  0.5f, 0.0f,
        -0.5f,  0.5f, 0.0f
    };
    unsigned int indices[] = {
        0, 1, 2,
        2, 3, 0
    };

    VertexArray VAO;
    VertexBuffer VBO;
    IndexBuffer IBO(indices, 6);
    VAO.bind();
    VBO.bind();
    VBO.setData(vertices, sizeof(vertices));
    IBO.bind();
    VAO.addVertexAttrib(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    VAO.unbind();
    VBO.unbind();
    IBO.unbind();

    Shader shader("basic.vert", "basic.frag");

    while (!glfwWindowShouldClose(window)) {
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        shader.use();
        VAO.bind();
        IBO.bind();
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        IBO.unbind();
        VAO.unbind();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}