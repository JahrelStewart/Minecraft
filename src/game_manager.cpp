#include "../Headers/game_manager.h"

GameManager::GameManager() {
    this->init();
}
GameManager::~GameManager() {
    delete GameManager::camera;
}

unsigned int GameManager::SCREENWIDTH = 1920;
unsigned int GameManager::SCREENHEIGHT = 1080;
float GameManager::deltaTime = 0.0f;
float GameManager::lastFrame = 0.0f;
GLFWwindow* GameManager::window = NULL;
Camera* GameManager::camera = new Camera(GameManager::SCREENWIDTH, GameManager::SCREENHEIGHT);

unsigned int GameManager::getScreenWidth() {
    return GameManager::SCREENWIDTH;
}
void GameManager::setScreenWidth(int x) {
    GameManager::SCREENWIDTH = x;
}

unsigned int GameManager::getScreenHeight() {
    return GameManager::SCREENHEIGHT;
}
void GameManager::setScreenHeight(int x) {
    GameManager::SCREENHEIGHT = x;
}

GLFWwindow* GameManager::getWindow() {
    return GameManager::window;
}

Camera* GameManager::getCamera() {
    return GameManager::camera;
}
void GameManager::setCamera(Camera& x) {
    GameManager::camera = &x;
}

void GameManager::framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);

    GameManager::SCREENWIDTH = width;
    GameManager::SCREENHEIGHT = height;


    //Here we ensure that the aspect ratio remains consistent and that the meshes aren't deformed on screen resize
    GameManager::camera->setProjection(glm::perspective(glm::radians(GameManager::camera->getZoom()), (float) GameManager::SCREENWIDTH / (float) GameManager::SCREENHEIGHT, 0.1f, 10000.0f));
}

void GameManager::getMouseInputs(GLFWwindow* window, double x, double y) {
    GameManager::camera->updateMouseInput(0.2f, x, y);
}

void GameManager::handleKeyboardInputs() {
    if (glfwGetKey(GameManager::getWindow(), GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(GameManager::getWindow(), true);

    if (glfwGetKey(GameManager::getWindow(), GLFW_KEY_W) == GLFW_PRESS)
        GameManager::camera->updateKeyboardInput(GameManager::deltaTime, 0);

    if (glfwGetKey(GameManager::getWindow(), GLFW_KEY_A) == GLFW_PRESS)
        GameManager::camera->updateKeyboardInput(GameManager::deltaTime, 2);

    if (glfwGetKey(GameManager::getWindow(), GLFW_KEY_S) == GLFW_PRESS)
        GameManager::camera->updateKeyboardInput(GameManager::deltaTime, 1);

    if (glfwGetKey(GameManager::getWindow(), GLFW_KEY_D) == GLFW_PRESS)
        GameManager::camera->updateKeyboardInput(GameManager::deltaTime, 3);
}

void GameManager::init() {
    // Initialize GLFW and OpenGL version
    glfwInit();

    // Create Window and rendering context using GLFW, resolution is 800x600
    const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
    GameManager::window = glfwCreateWindow(mode->width, mode->height, "Minecraft", glfwGetPrimaryMonitor(), NULL);

    if (GameManager::window == NULL) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        exit(1);
    }
    glfwMakeContextCurrent(GameManager::window);

    // Initialize GLEW
    glewExperimental = true; // Needed for core profile
    if (glewInit() != GLEW_OK) {
        std::cerr << "Failed to create GLEW" << std::endl;
        glfwTerminate();
        exit(1);
    }

    glfwSetFramebufferSizeCallback(GameManager::window, framebuffer_size_callback);
    glfwSetCursorPosCallback(GameManager::window, getMouseInputs);
    // glfwSetKeyCallback(GameManager::window, key_callback);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void GameManager::startFrame() {
    //update delta time
    float currentTime = glfwGetTime();
    GameManager::deltaTime = currentTime - GameManager::lastFrame;
    GameManager::lastFrame = currentTime;

    // background color
    glClearColor((float) 241 / 255, (float) 250 / 255, (float) 238 / 255, 1.0f);

    // reset viewport
    glViewport(0, 0, GameManager::getScreenWidth(), GameManager::getScreenHeight());
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void GameManager::endFrame() {
    // End frame
    glfwSwapBuffers(GameManager::getWindow());

    // Detect inputs
    glfwPollEvents();
}