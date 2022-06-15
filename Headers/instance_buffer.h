#pragma once

#include "texture.h"

class InstanceBuffer {
public:
    InstanceBuffer(const void* data, unsigned int count);
    ~InstanceBuffer();

    unsigned int getCount() const;

    void bind();
    void unbind();

private:
    unsigned int ID;
    unsigned int count;
};