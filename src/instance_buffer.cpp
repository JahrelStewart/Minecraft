#include "../Headers/instance_buffer.h"

InstanceBuffer::InstanceBuffer(const void* data, unsigned int count) : count{ count } {
    glGenBuffers(1, &this->ID);
    this->bind();
    glBufferData(GL_ARRAY_BUFFER, count * sizeof(glm::vec3), data, GL_STATIC_DRAW);
}

InstanceBuffer::~InstanceBuffer() {
    glDeleteBuffers(1, &this->ID);
}

void InstanceBuffer::bind() {
    glBindBuffer(GL_ARRAY_BUFFER, this->ID);
};

void InstanceBuffer::unbind() {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

unsigned int InstanceBuffer::getCount() const {
    return this->count;
}
