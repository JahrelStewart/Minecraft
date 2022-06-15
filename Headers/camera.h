#pragma once

#include <glm/glm.hpp>  // GLM is an optimized math library with syntax to similar to OpenGL Shading Language
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/matrix_decompose.hpp>

enum direction { FORWARD = 0, BACKWARD, LEFT, RIGHT };

class Camera {
public:
    //constructors and destructor
    Camera(unsigned int screenWidth, unsigned int screenHeight);
    ~Camera();

    //getters and setters
    glm::vec3 getPosition();
    void setPosition(glm::vec3 x);
    glm::vec3 getTarget();
    void setTarget(glm::vec3 x);
    glm::vec3 getDirection();
    void setDirection(glm::vec3 x);
    glm::vec3 getUp();
    void setUp(glm::vec3 x);
    glm::vec3 getRight();
    void setRight(glm::vec3 x);
    float getZoom();
    void setZoom(float x);
    glm::mat4 getView();
    void setView(glm::mat4 x);
    glm::mat4 getProjection();
    void setProjection(glm::mat4 x);

    void updateMouseInput(const float dt, const double x, const double y);
    void updateKeyboardInput(const float dt, const int direction);

private:
    glm::vec3 position;
    glm::vec3 target;
    glm::vec3 direction;
    glm::vec3 up;
    glm::vec3 right;
    glm::vec3 worldUp;

    float zoom;
    float pitch; //movement(i.e. the angle) around the y axis 
    float yaw; //movement(i.e. the angle) along the x axis 
    float roll;  //movement(i.e. the angle) along the z axis 
    float lookSensitivity;
    float moveSensitivity;

    //view matrix        
    glm::mat4 view;
    //projection matrix
    glm::mat4 projection;

    void updateCameraVectors();
};
