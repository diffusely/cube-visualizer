#include "DrawUI.h"

namespace UI {

    void DrawUI(RubikCube& cube, bool& randomize)
    {
        ImGui::Begin("Cube Controls", nullptr, ImGuiWindowFlags_NoMove);

        if (ImGui::Button("Top") && cube.GetRotationTime() <= 0.01f)
        {
            cube.SetRotState(true);
            cube.SetRotType(Rotation::Top);
        }

        if (ImGui::Button("Bottom") && cube.GetRotationTime() <= 0.01f)
        {
            cube.SetRotState(true);
            cube.SetRotType(Rotation::Bottom);
        }

        if (ImGui::Button("Left") && cube.GetRotationTime() <= 0.01f)
        {
            cube.SetRotState(true);
            cube.SetRotType(Rotation::Left);
        }

        if (ImGui::Button("Right") && cube.GetRotationTime() <= 0.01f)
        {
            cube.SetRotState(true);
            cube.SetRotType(Rotation::Right);
        }

        if (ImGui::Button("Front") && cube.GetRotationTime() <= 0.01f)
        {
            cube.SetRotState(true);
            cube.SetRotType(Rotation::Front);
        }

        if (ImGui::Button("Back") && cube.GetRotationTime() <= 0.01f)
        {
            cube.SetRotState(true);
            cube.SetRotType(Rotation::Back);
        }

        if (ImGui::Button("Randomize") && cube.GetRotationTime() <= 0.01f)
            randomize = true;

        if (ImGui::Button("Reset") && cube.GetRotationTime() <= 0.01f)
            cube.Reset();

        ImGui::End();
    }

    void DrawCube(
        RubikCube& cube,
        VertexArray& va,
        IndexBuffer& ib,
        Shader& shader,
        Renderer& renderer,
        const glm::mat4& proj,
        const glm::mat4& cubeRotation)
    {
        Camera::cameraPos.z = callback::cameraDistance;

        glm::mat4 view = glm::lookAt(
            Camera::cameraPos,
            glm::vec3(0, 0, 0),
            Camera::cameraUp
        );

        for (auto& c : cube.GetCubelets())
        {
            glm::mat4 model = glm::translate(
                glm::mat4(1.0f),
                c.position
            );

            model = c.rotation * model;
            model = glm::scale(model, glm::vec3(0.5f));
            model = cubeRotation * model;

            glm::mat4 mvp = proj * view * model;

            shader.Bind();
            shader.SetUniformMath4f("u_MVP", mvp);

            va.Bind();
            ib.Bind();

            renderer.Draw(va, ib, shader);
        }
    }
}