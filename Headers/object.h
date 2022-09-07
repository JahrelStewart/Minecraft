#pragma once

#include "vertex_array.h"

struct Rotation {
    glm::mat4 x;
    glm::mat4 y;
    glm::mat4 z;

    Rotation() { //default constructor
        this->x = glm::rotate(glm::mat4(1.0f), glm::radians(0.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        this->y = glm::rotate(glm::mat4(1.0f), glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        this->z = glm::rotate(glm::mat4(1.0f), glm::radians(0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    }

    Rotation(float x, float y, float z) { //constructor
        this->x = glm::rotate(glm::mat4(1.0f), glm::radians(x), glm::vec3(1.0f, 0.0f, 0.0f));
        this->y = glm::rotate(glm::mat4(1.0f), glm::radians(y), glm::vec3(0.0f, 1.0f, 0.0f));
        this->z = glm::rotate(glm::mat4(1.0f), glm::radians(z), glm::vec3(0.0f, 0.0f, 1.0f));
    }

    Rotation(const Rotation& copy) : x(copy.x), y(copy.y), z(copy.z) {} //copy constructor

    Rotation& operator=(const Rotation& rotation) { //assignemnt operator
        this->x = rotation.x;
        this->y = rotation.y;
        this->z = rotation.z;

        return *this;
    }

    glm::mat4 value() {
        return this->x * this->y * this->z;
    }
};

struct Properties {
    Rotation rotation;

    Properties() {
        this->rotation = { 0.0f, 0.0f, 0.0f };
    }

    Properties(Rotation r) {
        this->rotation = r;
    }
};

class Object {
public:
    Object(std::vector<float> vertices, std::vector<unsigned int> layout, std::vector<unsigned int>* indexes = nullptr, std::vector<glm::vec3>* instances = nullptr, std::vector<std::string> cubemap = {});
    ~Object();

    void setProperties(Rotation rotation);
    void draw(int shaderProgram, Camera* camera, const float dt, Properties props = { {0.0f, 0.0f, 0.0f} });

private:
    VertexArray* VAO;
    Texture texture;
    CubeMapTexture cubeMapTexture;

    std::vector<float> vertices;
    std::vector<unsigned int> layout;
    std::vector<glm::vec3>* instances;
    std::vector<unsigned int>* indexes;
    const char* textureFilePath; //check texture
    std::vector<std::string> cubeMapTextureFilePath;

    Properties props;

    void setupVII();
    void setupVIndex();
    void setupVInstances();
};
