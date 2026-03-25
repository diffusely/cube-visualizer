#pragma once
#include <glad/glad.h>

class VertexArray
{
public:
    VertexArray();
    ~VertexArray();

    void bind() const;
    void unbind() const;

    void addVertexAttrib(
        unsigned int index,
        int count,
        unsigned int type,
        bool normalized,
        int stride,
        const void* offset
    );

private:
    unsigned int m_ID;
};