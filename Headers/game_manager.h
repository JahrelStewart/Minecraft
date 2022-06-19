#pragma once

#include "object.h"

class GameManager {
public:
    //constructors and destructor
    GameManager();
    ~GameManager();

    //getters and setters
    static unsigned int getScreenWidth();
    static void setScreenWidth(int x);
    static unsigned int getScreenHeight();
    static void setScreenHeight(int x);
    static float getDeltaTime();
    static GLFWwindow* getWindow();
    static Camera* getCamera();
    static void setCamera(Camera& x);

    //functions
    static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
    static void getMouseInputs(GLFWwindow* window, double x, double y);
    static void handleKeyboardInputs();
    static void init();
    static void startFrame();
    static void endFrame();

private:
    static GLFWwindow* window;
    static Camera* camera;
    static unsigned int SCREENWIDTH;
    static unsigned int SCREENHEIGHT;
    static float deltaTime;	// Time between current frame and last frame
    static float lastFrame; // Time of last frame
    static float lastXpos, lastYpos; //last mouse X & Y screen positions    
};