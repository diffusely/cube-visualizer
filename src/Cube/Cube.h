#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"


class Cubelet
{
public:
    glm::vec3 position;
    glm::mat4 rotation;

    Cubelet(const glm::vec3& position)
        : position(position)
        , rotation(1.0f)
    {}

    glm::vec3 GetCurrentPos() const
    {
        glm::vec4 p = rotation * glm::vec4(position, 1.0f);
        return glm::vec3(p);
    }
};