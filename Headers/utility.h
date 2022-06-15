#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <assert.h> 

#define GLEW_STATIC 1   // This allows linking with Static Library on Windows, without DLL
#include <GL/glew.h>    // Include GLEW - OpenGL Extension Wrangler

#include <GLFW/glfw3.h> // GLFW provides a cross-platform interface for creating a graphical context,
                        // initializing OpenGL and binding inputs

#include "camera.h"

struct Shaders {
    std::string FloorVertexShader;
    std::string CubeVertexShader;
    std::string FragmentShader;
};

Shaders readShaders(const std::string& file);
int compileAndLinkShaders(const std::string& vertexShaderSRC, const std::string& fragmentShaderSRC, const std::string* geometryShaderSRC = nullptr);