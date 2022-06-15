#pragma once

#include "vertex_array.h"

class Object {
public:
    Object(std::vector<float> vertices, std::vector<unsigned int> layout, std::vector<glm::vec3>* instances = nullptr, std::vector<unsigned int>* indexes = nullptr, const char* textureFilePath = nullptr);
    ~Object();

    void draw(int shaderProgram, Camera* camera);

private:
    VertexArray* VAO;
    Texture texture;

    std::vector<float> vertices;
    std::vector<unsigned int> layout;
    std::vector<glm::vec3>* instances;
    std::vector<unsigned int>* indexes;
    const char* textureFilePath;

    void setupVII();
    void setupVIndex();
    void setupVInstances();
};
