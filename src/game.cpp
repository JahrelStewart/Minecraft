#include "../Headers/game_manager.h"
#include "../Headers/data.h"

int main() {
    GameManager::init();

    Shaders shader = readShaders("Shaders/shaders.shader");
    int floorShaderProgram = compileAndLinkShaders(shader.FloorVertexShader, shader.FragmentShader, nullptr);
    int cubeShaderProgram = compileAndLinkShaders(shader.CubeVertexShader, shader.FragmentShader, nullptr);

    Object floor(floorVertexArray, floorVertexLayout, &getFloorVertexInstances(), &floorIndexes, "Resources/Textures/tileTexture.png");
    Object cube(cubeVertexArray, cubeVertexLayout, nullptr, &cubeIndexes, "Resources/Textures/cubeTexture.png");

    while (!glfwWindowShouldClose(GameManager::getWindow())) {
//-----------------------------------------------------------------------------------------------------------------------------------
        // 1. First Pass: render depth of scene to texture (from light's perspective)


//------------------------------------------------------------------------------------------------------------------------------------------
        // 2. Second Pass: render scene as normal using the generated depth/shadow map  

        GameManager::startFrame();

        floor.draw(floorShaderProgram, GameManager::getCamera());
        cube.draw(cubeShaderProgram, GameManager::getCamera());

        GameManager::endFrame();

        GameManager::handleKeyboardInputs();
    }

    glDeleteProgram(floorShaderProgram);
    glDeleteProgram(cubeShaderProgram);

    // Shutdown GLFW
    glfwTerminate();

    return 0;
}
