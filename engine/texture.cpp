#include "texture.h"
#include "node.h"
#include <glm.hpp>
#include <GL/freeglut.h>
#include <iostream>
#include <FreeImage.h>


// Constructor
Texture::Texture(const std::string& name) : width(0), height(0) {
    Object::setId(Object::getNextId());
    Object::setName(name);
    //this->loadFromFile("default");
}

// Destructor
Texture::~Texture() {
    // Cleanup, if needed
}


// Load texture from a file
bool LIB_API Texture::loadFromFile(const std::string& filePath) {

    srand(0);
    for (int i = 0; i < 256 * 256 * 3; i++)
        bitmap[i] = rand() % 255;
    for (int i = 0; i < 256; i++) // white borders
    {
        unsigned char white[] = { 255, 255, 255 };
        memcpy(bitmap + i * 3, white, sizeof(unsigned char) * 3);
        memcpy(bitmap + 255 * 256 * 3 + i * 3, white, sizeof(unsigned char) * 3);
        memcpy(bitmap + i * 256 * 3, white, sizeof(unsigned char) * 3);
        memcpy(bitmap + i * 256 * 3 + 255 * 3, white, sizeof(unsigned char) * 3);
    }

    if (texId)
        glDeleteTextures(1, &texId);
    glGenTextures(1, &texId);
    glBindTexture(GL_TEXTURE_2D, texId);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 256, 256, 0, GL_RGB, GL_UNSIGNED_BYTE, bitmap);
    std::cout << "Texture ID: " << texId << std::endl;
    return true;
}

int Texture::getWidth() {
    return width;
}

int Texture::getHeight(){
    return width;
}

// Set texture settings
void LIB_API Texture::setTextureSettings(int width, int height) {
    this->width = width;
    this->height = height;
    // Add any other texture settings as needed
}

void LIB_API Texture::setTextureId(std::string filepath) {
    if (texId)
        glDeleteTextures(1, &texId);
    glGenTextures(1, &texId);
    glBindTexture(GL_TEXTURE_2D, texId);
    loadFromFile(filepath);
    //load from file

}


bool LIB_API Texture::render(glm::mat4 matrix, void* ptr) {
    glBindTexture(GL_TEXTURE_2D, texId);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, 1);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    
    return true;
}