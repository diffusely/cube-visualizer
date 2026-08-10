#include "RubikCube.h"
#include "RubikCube.h"
#include "RubikCube.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"


RubikCube::RubikCube()
{
    InitCubeletes();
}

void RubikCube::RotateTop()
{
    glm::mat4 r = glm::rotate(glm::mat4(1.0f), glm::radians(m_Rotate), glm::vec3(0, 1, 0));

    for (auto& c : m_Cubelets) {
        glm::vec3 p = c.GetCurrentPos();
        if (p.y > 0.4f)
            c.rotation = r * c.rotation;
    }
}

void RubikCube::RotateBottom()
{
    glm::mat4 r = glm::rotate(glm::mat4(1.0f), glm::radians(m_Rotate), glm::vec3(0, 1, 0));

    for (auto& c : m_Cubelets) {
        glm::vec3 p = c.GetCurrentPos();
        if (p.y < -0.4f)
            c.rotation = r * c.rotation;
    }
}

void RubikCube::RotateLeft()
{
    glm::mat4 r = glm::rotate(glm::mat4(1.0f), glm::radians(m_Rotate), glm::vec3(1, 0, 0));

    for (auto& c : m_Cubelets) {
        glm::vec3 p = c.GetCurrentPos();
        if (p.x < -0.4f)
            c.rotation = r * c.rotation;
    }
}

void RubikCube::RotateRight()
{
    glm::mat4 r = glm::rotate(glm::mat4(1.0f), glm::radians(m_Rotate), glm::vec3(1, 0, 0));

    for (auto& c : m_Cubelets) {
        glm::vec3 p = c.GetCurrentPos();
        if (p.x > 0.4f)
            c.rotation = r * c.rotation;
    }
}

void RubikCube::RotateFront()
{
    glm::mat4 r = glm::rotate(glm::mat4(1.0f), glm::radians(m_Rotate), glm::vec3(0, 0, 1));

    for (auto& c : m_Cubelets) {
        glm::vec3 p = c.GetCurrentPos();
        if (p.z > 0.4f)
            c.rotation = r * c.rotation;
    }
}

void RubikCube::RotateBack()
{
    glm::mat4 r = glm::rotate(glm::mat4(1.0f), glm::radians(m_Rotate), glm::vec3(0, 0, 1));

    for (auto& c : m_Cubelets) {
        glm::vec3 p = c.GetCurrentPos();
        if (p.z < -0.4f)
            c.rotation = r * c.rotation;
    }
}

void RubikCube::Update()
{
  

    UpdateRotation();
    UpdateImGui();

}

void RubikCube::UpdateRotation()
{
    if (m_Rotation) {

        switch (m_Type)
        {
        case Rotation::Top:
            RotateTop();
            break;

        case Rotation::Bottom:
            RotateBottom();
            break;

        case Rotation::Left:
            RotateLeft();
            break;

        case Rotation::Right:
            RotateRight();
            break;

        case Rotation::Front:
            RotateFront();
            break;

        case Rotation::Back:
            RotateBack();
            break;

        default:
            break;
        }

        m_Time += m_Rotate;
    }

    if (m_Time >= 90.0f) {
        m_Rotation = false;
        m_Time = 0;
        m_Type = Rotation::None;
    }
}

void RubikCube::UpdateImGui()
{


}

void RubikCube::SetRotType(Rotation type)
{
    m_Type = type;
}

void RubikCube::SetRotState(bool state)
{
    m_Rotation = state;
}

const std::vector<Cubelet>& RubikCube::GetCubelets() const
{
    return m_Cubelets;
}

void RubikCube::InitCubeletes()
{
    for (int x = -1; x <= 1; x++) {
        for (int y = -1; y <= 1; y++) {
            for (int z = -1; z <= 1; z++) {
                m_Cubelets.push_back(Cubelet{ glm::vec3(x * 0.5f, y * 0.5f, z * 0.5f) });
            }
        }
    }
}



