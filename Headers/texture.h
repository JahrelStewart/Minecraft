#pragma once

#include "index_buffer.h"

#include "../Resources/stb_image/stb_image.h"

class Texture {
public:
    Texture();
    ~Texture();

    unsigned int ID;

    void bind();
    void unbind();

    void loadTexture(const char* filepath);

private:
    int width;
    int height;
    int channels;
};

class CubeMapTexture {
public:
    CubeMapTexture();
    ~CubeMapTexture();

    unsigned int ID;

    void bind();
    void unbind();

    void loadTexture(std::vector<std::string> cubemap);

private:
    int width;
    int height;
    int channels;
};