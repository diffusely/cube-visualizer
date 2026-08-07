#pragma once
#include <glad/glad.h>
#include "graphics/VertexBuffer/VertexBuffer.h"
#include "graphics/VertexBufferLayout/VertexBufferLayout.h"

class VertexArray
{
public:
    VertexArray();
    ~VertexArray();

    void AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout);

    void Bind() const;
    void Unbind() const;

private:
    unsigned int m_RendererID;
};