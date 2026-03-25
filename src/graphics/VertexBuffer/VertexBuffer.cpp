#include "VertexBuffer.h"

VertexBuffer::VertexBuffer()
{
    glGenBuffers(1, &m_ID);
}

VertexBuffer::VertexBuffer(const void* data, unsigned int size)
    : m_ID(0)
{
    glGenBuffers(1, &m_ID);
    glBindBuffer(GL_ARRAY_BUFFER, m_ID);
    glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

VertexBuffer::~VertexBuffer()
{
    glDeleteBuffers(1, &m_ID);
}

void VertexBuffer::bind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, m_ID);
}

void VertexBuffer::unbind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VertexBuffer::setData(const void* data, unsigned int size)
{
    bind();
    glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}
