#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"


#include "Window/Window.h"
#include "Cube/RubikCube.h"
#include "Vertices/Vertices.h"
#include "Core/DrawUI.h"

const unsigned int SCR_WIDTH = 1400;
const unsigned int SCR_HEIGHT = 960;


int main()
{
    //I Am Laugh Under The Weeping Moon
    Window window(1400, 900, "Cube");

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    VertexArray va;
    VertexBuffer vb(CubeletMesh::vertices, sizeof(CubeletMesh::vertices));
    VertexBufferLayout layout;

    layout.Push<float>(3);
    layout.Push<float>(3);

    va.AddBuffer(vb, layout);

    IndexBuffer ib(CubeletMesh::indices, 72);
    Shader shader("shaders/basic.shader");

    glm::mat4 proj = glm::perspective(
        glm::radians(45.0f),
        (float)SCR_WIDTH / SCR_HEIGHT,
        0.1f,
        100.0f
    );

    glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(-3, 0, -3));
    glm::mat4 model = glm::mat4(1.0f);

    glm::mat4 mvp = proj * view * model;

    shader.Bind();
    shader.SetUniformMath4f("u_MVP", mvp);

    Renderer renderer;

    srand(time(0));
    glEnable(GL_MULTISAMPLE);
    glEnable(GL_BLEND);
    glEnable(GL_DEPTH_TEST);

    ImGui::CreateContext();
    ImGui::StyleColorsDark();

    ImGui_ImplGlfwGL3_Init(window.GetNativeWindow(), false);
    
    RubikCube cube;
    
    int count = 20;
    int num = count;
    bool randomize = false;
    while (!window.ShouldClose()) {


        glClearColor(0.1f, 0.1f, 0.1f, 0.1f);

        renderer.Clear();

        ImGui_ImplGlfwGL3_NewFrame();

        UI::DrawUI(cube, randomize);

        if (randomize && num && cube.GetRotationTime() <= 0.1f) {
            cube.Randomize();
            --num;
        }

        if (num == 0) {
            randomize = false;
            num = count;
        }

        cube.Update();


        glm::mat4 cubeRotation = glm::mat4(1.0f);

        cubeRotation = glm::rotate(
            cubeRotation,
            glm::radians(callback::cubeRotX),
            glm::vec3(1, 0, 0)
        );


        cubeRotation = glm::rotate(
            cubeRotation,
            glm::radians(callback::cubeRotY),
            glm::vec3(0, 1, 0)
        );


        UI::DrawCube(
            cube,
            va,
            ib,
            shader,
            renderer,
            proj,
            cubeRotation
        );
       
        ImGui::Render();
        ImGui_ImplGlfwGL3_RenderDrawData(ImGui::GetDrawData());
        window.Update();
    }

    ImGui_ImplGlfwGL3_Shutdown();
    ImGui::DestroyContext();
    return 0;
}