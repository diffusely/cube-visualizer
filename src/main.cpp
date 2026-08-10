#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw_gl3.h"

#include "Graphics/IndexBuffer/IndexBuffer.h"
#include "Graphics/VertexBuffer/VertexBuffer.h"
#include "Graphics/VertexBufferLayout/VertexBufferLayout.h"
#include "Graphics/VertexArray/VertexArray.h"
#include "Graphics/Shader/Shader.h"
#include "Graphics/Renderer/Renderer.h"
#include "Graphics/Texture/Texture.h"
#include "Tests/TestClearColor.h"
#include "Callback/CallBack.h"
#include "Window/Window.h"
#include "Cube/RubikCube.h"
#include "Vertices/Vertices.h"

const unsigned int SCR_WIDTH = 1400;
const unsigned int SCR_HEIGHT = 960;

glm::vec3 cameraPos = glm::vec3(
    -0.347205f,
    4.42031f,
    4.11971f
);

glm::vec3 cameraUp = glm::vec3(
    0.0f,
    1.0f,
    0.0f
);

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

  
    glEnable(GL_BLEND);
    glEnable(GL_DEPTH_TEST);


    ImGui::CreateContext();
    ImGui::StyleColorsDark();


    ImGui_ImplGlfwGL3_Init(window.GetNativeWindow(), false);
    


    RubikCube cube;


    bool rotation = false;
    float rotate = 5.0f;
    float time = 0.0f;
    std::string roatationType = "";
    while (!window.ShouldClose()) {


        glClearColor(0.1f, 0.1f, 0.1f, 0.1f);

        renderer.Clear();

        ImGui_ImplGlfwGL3_NewFrame();

        ImGui::Begin("Cube Controls");

        if (ImGui::Button("Top"))
        {
            cube.SetRotState(true);
            cube.SetRotType(Rotation::Top);
        }

        if (ImGui::Button("Bottom"))
        {
            cube.SetRotState(true);
            cube.SetRotType(Rotation::Bottom);
        }

        if (ImGui::Button("Left"))
        {
            cube.SetRotState(true);
            cube.SetRotType(Rotation::Left);
        }

        if (ImGui::Button("Right"))
        {
            cube.SetRotState(true);
            cube.SetRotType(Rotation::Right);
        }

        if (ImGui::Button("Front"))
        {
            cube.SetRotState(true);
            cube.SetRotType(Rotation::Front);
        }

        if (ImGui::Button("Back"))
        {
            cube.SetRotState(true);
            cube.SetRotType(Rotation::Back);
        }

        ImGui::End();

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



        for (auto& c : cube.GetCubelets()) {

            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, c.position);
            model = c.rotation * model;
            model = glm::scale(model, glm::vec3(0.5f));


            model = cubeRotation * model;

            glm::mat4 view = glm::lookAt(cameraPos, glm::vec3(0, 0, 0), cameraUp);
            glm::mat4 mvp = proj * view * model;


            shader.Bind();
            shader.SetUniformMath4f("u_MVP", mvp);


            va.Bind();
            ib.Bind();

            renderer.Draw(va, ib, shader);
        }
       



        ImGui::Render();
        ImGui_ImplGlfwGL3_RenderDrawData(ImGui::GetDrawData());
        window.Update();
    }

    ImGui_ImplGlfwGL3_Shutdown();
    ImGui::DestroyContext();
    return 0;
}