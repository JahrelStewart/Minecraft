#include "../Headers/game_manager.h"
#include "../Headers/data.h"

int main() {
    GameManager::init();

    Shaders shader = readShaders("Shaders/shaders.shader");
    // int floorShaderProgram = compileAndLinkShaders(shader.FloorVertexShader, shader.FloorFragmentShader, nullptr);
    int cubeShaderProgram = compileAndLinkShaders(shader.CubeVertexShader, shader.CubeFragmentShader, nullptr);

    // Object floor(floorVertexArray, floorVertexLayout, &floorIndexes, &getFloorVertexInstances());
    Object cube(cubeVertexArray, cubeVertexLayout, &cubeIndexes, nullptr, cubeMapFaces);

    while (!glfwWindowShouldClose(GameManager::getWindow())) {
        GameManager::startFrame();

        // floor.draw(floorShaderProgram, GameManager::getCamera(), GameManager::getDeltaTime(), { {-90.0f, 0.0f, 0.0f} });
        cube.draw(cubeShaderProgram, GameManager::getCamera(), GameManager::getDeltaTime());

        GameManager::endFrame();

        GameManager::handleKeyboardInputs();
    }

    // glDeleteProgram(floorShaderProgram);
    glDeleteProgram(cubeShaderProgram);

    // Shutdown GLFW
    glfwTerminate();

    return 0;
}
