#include "../Headers/vertex_array.h"

VertexArray::VertexArray() {
    glGenVertexArrays(1, &this->ID);
    this->bind();
    this->bufferCount = 0;
}

VertexArray::~VertexArray() {
    glDeleteVertexArrays(1, &this->ID);
}

void VertexArray::bind() {
    glBindVertexArray(this->ID);
};

void VertexArray::unbind() {
    glBindVertexArray(0);
}

void VertexArray::addBufferLayout(VertexBuffer& object) {
    object.bind();
    unsigned int offset = 0;
    const auto& attributes = object.getAttributes();
    unsigned int i;

    for (i = this->bufferCount; i < attributes.size() + this->bufferCount; i++) {
        const auto& attribute = attributes[i];

        glVertexAttribPointer(i,
            attribute.length,
            attribute.type,
            GL_FALSE,
            object.getLayoutSize(),
            (void*) (intptr_t) offset
        );
        glEnableVertexAttribArray(i);

        offset += attribute.length * Info::getTypeSize(attribute.type);
    }

    this->bufferCount = i;
}

void VertexArray::addInstanceBufferLayout(InstanceBuffer& object) {
    object.bind();

    glVertexAttribPointer(this->bufferCount,
        3,
        GL_FLOAT,
        GL_FALSE,
        sizeof(glm::vec3),
        (const void*) 0
    );
    glEnableVertexAttribArray(this->bufferCount);
    glVertexAttribDivisor(this->bufferCount, 1);

    this->bufferCount++;
}

