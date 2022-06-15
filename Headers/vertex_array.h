#pragma once

#include "vertex_buffer.h"

class VertexArray {
public:
    VertexArray();
    ~VertexArray();

    unsigned int ID;

    void bind();
    void unbind();

    void addBufferLayout(VertexBuffer& object);
    void addInstanceBufferLayout(InstanceBuffer& object);

private:
    unsigned int bufferCount;
};

