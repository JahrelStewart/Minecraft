#define STB_IMAGE_IMPLEMENTATION
#include "../Headers/texture.h"


Texture::Texture() {
    glGenTextures(1, &this->ID);
    this->bind();
}

Texture::~Texture() {
    glDeleteTextures(1, &this->ID);
}

void Texture::bind() {
    glBindTexture(GL_TEXTURE_2D, this->ID);
};

void Texture::unbind() {
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::loadTexture(const char* filepath) {
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    stbi_set_flip_vertically_on_load(true);
    unsigned char* data = stbi_load(filepath, &this->width, &this->height, &this->channels, 4);

    if (data) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, this->width, this->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else {
        std::cout << "Unable to Load Texture!" << std::endl;
    }

    stbi_image_free(data);
}

//-----------------------------------------------------------------------------

CubeMapTexture::CubeMapTexture() {
    glGenTextures(1, &this->ID);
    this->bind();
}

CubeMapTexture::~CubeMapTexture() {
    glDeleteTextures(1, &this->ID);
}

void CubeMapTexture::bind() {
    glBindTexture(GL_TEXTURE_CUBE_MAP, this->ID);
};

void CubeMapTexture::unbind() {
    glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
}

void CubeMapTexture::loadTexture(std::vector<std::string> cubemap) {
    this->bind();

    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    for (unsigned int i = 0; i < cubemap.size(); i++) {
        unsigned char* data = stbi_load(cubemap[i].c_str(), &this->width, &this->height, &this->channels, 0);

        if (data) {
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, this->width, this->height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        }
        else {
            std::cout << "Unable to Load CubeMap Texture: " << cubemap[i] << std::endl;
        }

        stbi_image_free(data);
    }
}