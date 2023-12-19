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

    std::cout << "Loading texture from file: " << filePath << std::endl;

    if (texId)
        glDeleteTextures(1, &texId);

    glGenTextures(1, &texId);
    glBindTexture(GL_TEXTURE_2D, texId);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    FIBITMAP* bitmap = FreeImage_Load(FreeImage_GetFileType(filePath.c_str(), 0), filePath.c_str());

    std::cout << "BPP: " << FreeImage_GetBPP(bitmap) << std::endl;

    // Flip texture
    FreeImage_FlipVertical(bitmap);

    if (FreeImage_GetBPP(bitmap) == 32) {   
        // 32 bits -> RGBA colors
        gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA,
            FreeImage_GetWidth(bitmap), FreeImage_GetHeight(bitmap),
            GL_BGRA_EXT, GL_UNSIGNED_BYTE,
            (void*)FreeImage_GetBits(bitmap));
    }
    else if (FreeImage_GetBPP(bitmap) == 24) {
        // 24 bits -> RGB colors
        gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB,
            FreeImage_GetWidth(bitmap), FreeImage_GetHeight(bitmap),
            GL_BGR_EXT, GL_UNSIGNED_BYTE,
            (void*)FreeImage_GetBits(bitmap));
    }

    // Release bitmap
    FreeImage_Unload(bitmap);
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
    loadFromFile(filepath);
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