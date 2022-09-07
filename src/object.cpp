#include "../Headers/object.h"

Object::Object(std::vector<float> vertices, std::vector<unsigned int> layout, std::vector<unsigned int>* indexes, std::vector<glm::vec3>* instances, std::vector<std::string> cubemap) {

    this->vertices = vertices;
    this->layout = layout;
    this->indexes = indexes;
    this->cubeMapTextureFilePath = cubemap;

    this->setProperties({ 0.0f, 0.0f, 0.0f });

    this->VAO = new VertexArray();

    // if (instances != nullptr && indexes != nullptr) {
    //     this->instances = instances;
    //     this->setupVII();
    // }
    // else if (instances != nullptr) {
    //     this->instances = instances;
    //     this->setupVInstances();
    // }
    // else {
    this->setupVIndex();
    // }
}

Object::~Object() {
    delete this->VAO;
    delete this->instances;
    delete this->indexes;
    delete this->textureFilePath;
}

void Object::setProperties(Rotation rotation) {
    this->props.rotation = rotation;
}

void Object::setupVII() { //check texture
    this->VAO->bind();

    VertexBuffer objectBuffer(&(this->vertices)[0], this->vertices.size() * sizeof(this->vertices[0]));
    for (unsigned int length : this->layout) {
        objectBuffer.addAttribute<float>(length);
    }

    this->VAO->addBufferLayout(objectBuffer);

    InstanceBuffer instancesBuffer(&(*(this->instances))[0], this->instances->size());
    this->VAO->addInstanceBufferLayout(instancesBuffer);

    IndexBuffer indexBuffer(&(*(this->indexes))[0], this->indexes->size());

    this->texture.bind();
    this->texture.loadTexture(textureFilePath);

    this->VAO->unbind();
}

void Object::setupVInstances() { //check texture
    this->VAO->bind();

    VertexBuffer objectBuffer(&(this->vertices)[0], this->vertices.size() * sizeof(this->vertices[0]));
    for (unsigned int length : this->layout) {
        objectBuffer.addAttribute<float>(length);
    }

    this->VAO->addBufferLayout(objectBuffer);

    InstanceBuffer instancesBuffer(&(*(this->instances))[0], this->instances->size());
    this->VAO->addInstanceBufferLayout(instancesBuffer);

    this->texture.bind();
    this->texture.loadTexture(textureFilePath);

    this->VAO->unbind();
}

void Object::setupVIndex() {
    this->VAO->bind();

    VertexBuffer objectBuffer(&(this->vertices)[0], this->vertices.size() * sizeof(this->vertices[0]));
    for (unsigned int length : this->layout) {
        objectBuffer.addAttribute<float>(length);
    }

    this->VAO->addBufferLayout(objectBuffer);

    IndexBuffer indexBuffer(&(*(this->indexes))[0], this->indexes->size());

    this->cubeMapTexture.loadTexture(this->cubeMapTextureFilePath);

    this->VAO->unbind();
}

void Object::draw(int shaderProgram, Camera* camera, const float dt, Properties props) {
    glUseProgram(shaderProgram);
    int model_location_MVP = glGetUniformLocation(shaderProgram, "u_Model_View_Projection");
    int model_location = glGetUniformLocation(shaderProgram, "u_Model");
    int texture_location = glGetUniformLocation(shaderProgram, "cubemap");

    //calculate model matrix : the transform of the object
    glm::mat4 model = props.rotation.x;
    //calculate MVP matrix
    glm::mat4 transformation_result = camera->getProjection() * camera->getView(dt) * model;
    glUniformMatrix4fv(model_location, 1, GL_FALSE, glm::value_ptr(model));
    glUniformMatrix4fv(model_location_MVP, 1, GL_FALSE, glm::value_ptr(transformation_result));

    this->VAO->bind();

    glUniform1i(texture_location, 0);
    glActiveTexture(GL_TEXTURE0);
    this->cubeMapTexture.bind();

    // if (this->instances != nullptr) {
    //     //to display floor as a plane:
    //     // glDrawElementsInstanced(GL_TRIANGLES, this->indexes->size(), GL_UNSIGNED_INT, nullptr, this->instances->size());

    //     glLineWidth(2.0f);

    //     //to display floor as a grid:
    //     glDrawElementsInstanced(GL_LINE_LOOP, this->indexes->size(), GL_UNSIGNED_INT, nullptr, this->instances->size());
    // }
    // else {
    glDrawElements(GL_TRIANGLES, this->indexes->size(), GL_UNSIGNED_INT, 0);
    // }

    this->VAO->unbind();
}
