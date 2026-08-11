#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw_gl3.h"
#include "Cube/RubikCube.h"
#include "Graphics/Shader/Shader.h"
#include "CallBack/CallBack.h"
#include "Graphics/VertexArray/VertexArray.h"
#include "Graphics/IndexBuffer/IndexBuffer.h"
#include "Graphics/Renderer/Renderer.h"
#include "Camera.h"

class RubikCube;
enum class Rotation;

namespace UI {
	void DrawUI(RubikCube& cube, bool& randomize);

    void DrawCube(
        RubikCube& cube,
        VertexArray& va,
        IndexBuffer& ib,
        Shader& shader,
        Renderer& renderer,
        const glm::mat4& proj,
        const glm::mat4& cubeRotation
    );
}