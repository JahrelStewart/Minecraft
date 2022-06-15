#include "../Headers/vertex_buffer.h"

VertexBuffer::VertexBuffer(const void* data, unsigned int size) {
    glGenBuffers(1, &this->ID);
    this->bind();
    glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
    this->layoutSize = 0;
}

VertexBuffer::~VertexBuffer() {
    glDeleteBuffers(1, &this->ID);
}

void VertexBuffer::bind() {
    glBindBuffer(GL_ARRAY_BUFFER, this->ID);
};

void VertexBuffer::unbind() {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

unsigned int VertexBuffer::getLayoutSize() const {
    return this->layoutSize;
}

const std::vector<Info>& VertexBuffer::getAttributes() const {
    return this->attributes;
}

template<>
void VertexBuffer::addAttribute<unsigned int>(unsigned int length) {
    this->attributes.push_back({ length, GL_UNSIGNED_INT });
    this->layoutSize += length * sizeof(float);
}

template<>
void VertexBuffer::addAttribute<float>(unsigned int length) {
    this->attributes.push_back({ length, GL_FLOAT });
    this->layoutSize += length * sizeof(unsigned int);
}