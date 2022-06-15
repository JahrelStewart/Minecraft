#pragma once

#include "instance_buffer.h"

struct Info {
    unsigned int length;
    unsigned int type;

    static unsigned int getTypeSize(unsigned int type) {
        switch (type) {
        case GL_FLOAT: return sizeof(float);
        case GL_UNSIGNED_INT: return sizeof(unsigned int);
        }

        assert(false);
        return 0;
    }
};

class VertexBuffer {
public:
    VertexBuffer(const void* data, unsigned int size);
    ~VertexBuffer();

    unsigned int getLayoutSize() const;
    const std::vector<Info>& getAttributes() const;

    void bind();
    void unbind();

    template<typename T>
    void addAttribute(unsigned int length);

private:
    unsigned int ID;
    std::vector<Info> attributes;
    unsigned int layoutSize;
};

