#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <stb/stb_image.h>
#include <iostream>
#include <cmath>
#include "Shader.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
    if (window == NULL) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    Shader ourShader("shaders/basic.vert", "shaders/basic.frag");

    float vertices[] = {

        // BACK FACE (red)
        -0.5f,  0.5f, -0.5f,   1.0f, 0.0f, 0.0f, // 0
         0.5f,  0.5f, -0.5f,   1.0f, 0.0f, 0.0f, // 1
        -0.5f, -0.5f, -0.5f,   1.0f, 0.0f, 0.0f, // 2
         0.5f, -0.5f, -0.5f,   1.0f, 0.0f, 0.0f, // 3


         // FRONT FACE (green)
         -0.5f,  0.5f,  0.5f,   0.0f, 1.0f, 0.0f, // 4
          0.5f,  0.5f,  0.5f,   0.0f, 1.0f, 0.0f, // 5
         -0.5f, -0.5f,  0.5f,   0.0f, 1.0f, 0.0f, // 6
          0.5f, -0.5f,  0.5f,   0.0f, 1.0f, 0.0f, // 7


          // LEFT FACE (blue)
          -0.5f,  0.5f, -0.5f,   0.0f, 0.0f, 1.0f, // 8
          -0.5f, -0.5f, -0.5f,   0.0f, 0.0f, 1.0f, // 9
          -0.5f,  0.5f,  0.5f,   0.0f, 0.0f, 1.0f, // 10
          -0.5f, -0.5f,  0.5f,   0.0f, 0.0f, 1.0f, // 11


          // RIGHT FACE (yellow)
           0.5f,  0.5f, -0.5f,   1.0f, 1.0f, 0.0f, // 12
           0.5f, -0.5f, -0.5f,   1.0f, 1.0f, 0.0f, // 13
           0.5f,  0.5f,  0.5f,   1.0f, 1.0f, 0.0f, // 14
           0.5f, -0.5f,  0.5f,   1.0f, 1.0f, 0.0f, // 15


           // TOP FACE (white)
           -0.5f, 0.5f, -0.5f,    1.0f, 1.0f, 1.0f, // 16
            0.5f, 0.5f, -0.5f,    1.0f, 1.0f, 1.0f, // 17
           -0.5f, 0.5f,  0.5f,    1.0f, 1.0f, 1.0f, // 18
            0.5f, 0.5f,  0.5f,    1.0f, 1.0f, 1.0f, // 19


            // BOTTOM FACE (orange)
            -0.5f, -0.5f, -0.5f,   1.0f, 0.5f, 0.0f, // 20
             0.5f, -0.5f, -0.5f,   1.0f, 0.5f, 0.0f, // 21
            -0.5f, -0.5f,  0.5f,   1.0f, 0.5f, 0.0f, // 22
             0.5f, -0.5f,  0.5f,   1.0f, 0.5f, 0.0f  // 23
    };

    unsigned int indices[] = {

        // back
        0,1,2,
        1,3,2,

        // front
        4,6,5,
        5,6,7,

        // left
        8,9,10,
        9,11,10,

        // right
        12,14,13,
        13,14,15,

        // top
        16,18,17,
        17,18,19,

        // bottom
        20,21,22,
        21,23,22
    };

    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    unsigned int VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // position
    glVertexAttribPointer(
        0,
        3,
        GL_FLOAT,
        GL_FALSE,
        6 * sizeof(float),
        (void*)0
    );
    glEnableVertexAttribArray(0);


    // color
    glVertexAttribPointer(
        1,
        3,
        GL_FLOAT,
        GL_FALSE,
        6 * sizeof(float),
        (void*)(3 * sizeof(float))
    );
    glEnableVertexAttribArray(1);


    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    glEnable(GL_DEPTH_TEST);
    while (!glfwWindowShouldClose(window))
    {

        processInput(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // activate shader
        ourShader.use();

        // create transformations
        glm::mat4 model = glm::mat4(1.0f); 
        glm::mat4 view = glm::mat4(1.0f);
        glm::mat4 projection = glm::mat4(1.0f);

        model = glm::rotate(model, (float)glfwGetTime() * glm::radians(120.0f), glm::vec3(0.5f, 1.0f, 0.0f));
        view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
        projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);

        unsigned int modelLoc = glGetUniformLocation(ourShader.get_ID(), "model");
        unsigned int viewLoc = glGetUniformLocation(ourShader.get_ID(), "view");

        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &view[0][0]);

        ourShader.setMat4("projection", projection);


        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

        //glDrawArrays(GL_TRIANGLES, 0, 36);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }


    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);

    glfwTerminate();
    return 0;
}

