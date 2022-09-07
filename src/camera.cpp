#include "../Headers/camera.h"

Camera::Camera(unsigned int screenWidth, unsigned int screenHeight) {
    //deafault camera values:
    this->zoom = 45.0f;
    this->pitch = 0.0f;
    this->yaw = -90.0f;
    this->roll = 0.0f;
    this->moveSensitivity = 15.0f;
    this->lookSensitivity = 7.0f;

    this->position = glm::vec3(0.0f, 5.0f, 25.0f);
    this->target = glm::vec3(0.0f, 5.0f, -1.0f);
    this->worldUp = glm::vec3(0.0f, 1.0f, 0.0f);
    this->direction = glm::normalize(this->position - this->target);
    this->right = glm::normalize(glm::cross(this->worldUp, this->direction));
    this->up = glm::normalize(glm::cross(this->direction, this->right));


    //calculate view matrix..which is essentially the view of the camera        
    this->view = glm::lookAt(this->position, this->position + this->target, this->worldUp);
    //create projection matrix
    this->projection = glm::perspective(glm::radians(this->zoom), (float) screenWidth / (float) screenHeight, 0.1f, 10000.0f);
}
Camera::~Camera() {}

glm::vec3 Camera::getPosition() {
    return this->position;
}
void Camera::setPosition(glm::vec3 x) {
    this->position = x;
}
glm::vec3 Camera::getTarget() {
    return this->target;
}
void Camera::setTarget(glm::vec3 x) {
    this->target = x;
}
glm::vec3 Camera::getDirection() {
    return this->direction;
}
void Camera::setDirection(glm::vec3 x) {
    this->direction = x;
}
glm::vec3 Camera::getUp() {
    return this->up;
}
void Camera::setUp(glm::vec3 x) {
    this->up = x;
}
glm::vec3 Camera::getRight() {
    return this->right;
}
void Camera::setRight(glm::vec3 x) {
    this->right = x;
}
float Camera::getZoom() {
    return this->zoom;
}
void Camera::setZoom(float x) {
    this->zoom = x;
}
glm::mat4 Camera::getView(const float dt) {
    this->updateCameraVectors(dt);
    this->view = glm::lookAt(this->position, this->position + this->target, this->up);
    return this->view;
}
void Camera::setView(glm::mat4 x) {
    this->view = x;
}
glm::mat4 Camera::getProjection() {
    return this->projection;
}
void Camera::setProjection(glm::mat4 x) {
    this->projection = x;
}

void Camera::rotate(const float dt, const double x, const double y) {
    float speed = this->lookSensitivity * dt;

    this->pitch += static_cast<float>(y) * speed;
    this->yaw += static_cast<float>(x) * speed;

    this->pitch = std::min(std::max(this->pitch, -89.0f), 89.0f);
}

void Camera::translate(const float dt, const int direction) {
    float speed = this->moveSensitivity * dt;

    switch (direction) {
    case direction::FORWARD:
        this->position += this->target * speed;
        break;

    case direction::BACKWARD:
        this->position -= this->target * speed;
        break;

    case direction::LEFT:
        this->position += this->right * speed;
        break;

    case direction::RIGHT:
        this->position -= this->right * speed;
        break;

    default: break;

    }
}

void Camera::updateCameraVectors(const float dt) {
    //added camera rotation smoothness using LERP
    float smoothedStep = 20.0f * dt;
    this->target.x = std::lerp(this->target.x, cos(glm::radians(this->yaw)) * cos(glm::radians(this->pitch)), smoothedStep);
    this->target.y = std::lerp(this->target.y, sin(glm::radians(this->pitch)), smoothedStep);
    this->target.z = std::lerp(this->target.z, sin(glm::radians(this->yaw)) * cos(glm::radians(this->pitch)), smoothedStep);

    this->right = glm::normalize(glm::cross(this->up, this->target));
    this->target = glm::normalize(this->target);
}

