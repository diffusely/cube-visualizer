#pragma once
#include <glad/glad.h>

class VertexBuffer
{
public:
    VertexBuffer();
    VertexBuffer(const void* data, unsigned int size);
    ~VertexBuffer();

    void bind() const;
    void unbind() const;

    void setData(const void* data, unsigned int size);

private:
    unsigned int m_ID;
};