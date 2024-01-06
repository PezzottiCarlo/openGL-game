/**
 * @file    texture.h
 * @brief   Texture class definition
 *
 * This file contains the declaration of the Texture class, which is a derived class from the Object class.
 * It represents a texture with functionalities to load from a file, set texture settings, and render.
 *
 * @author  Jari Näser (C) SUPSI [jari.naeser@student.supsi.ch]
 * @author  Carlo Pezzotti (C) SUPSI [carlo.pezzotti@student.supsi.ch]
 */

#pragma once

 ////////////
 // #INCLUDE //
 ////////////
#include <string>     // Include for std::string

#include "lib.h"
#include "object.h"  // Assuming you have an "object.h" header for the base class

// OpenGL constants for texture anisotropy
#define GL_TEXTURE_MAX_ANISOTROPY_EXT        0x84FE
#define GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT    0x84FF

/////////////
// CLASSES //
/////////////

/**
 * @brief Texture class, extends Object.
 */
class LIB_API Texture : public Object {
    //////////
public: //
    //////////
        /**
         * @brief Constructor for Texture.
         *
         * @param name The name of the texture.
         */
    Texture(const std::string& name);

    /**
     * @brief Destructor for Texture.
     */
    ~Texture();

    /**
     * @brief Load texture from a file.
     *
     * @param filePath The file path of the texture.
     * @return A boolean indicating the success of loading the texture.
     */
    bool loadFromFile(const std::string& filePath);

    /**
     * @brief Set texture settings (hypothetical example).
     *
     * @param width The width of the texture.
     * @param height The height of the texture.
     */
    void setTextureSettings(int width, int height);

    /**
     * @brief Set texture ID.
     *
     * @param textureId The texture ID.
     */
    void setTextureId(std::string textureId);

    /**
     * @brief Render function for the texture.
     *
     * @param transform The transformation matrix for rendering the texture.
     * @param data Additional data for rendering (optional).
     * @return A boolean indicating the success of the rendering operation.
     */
    virtual bool render(glm::mat4 transform, void* data) override;

    /**
     * @brief Get the width of the texture.
     *
     * @return The width of the texture.
     */
    int getWidth();

    /**
     * @brief Get the height of the texture.
     *
     * @return The height of the texture.
     */
    int getHeight();

    /**
     * @brief Test method for the texture.
     *
     * @return An integer indicating the result of the test.
     */
    static int test();

    ///////////
private: //
    ///////////
        /**
         * @brief File path of the texture.
         */
    std::string filePath;

    /**
     * @brief Width of the texture.
     */
    int width;

    /**
     * @brief Height of the texture.
     */
    int height;

    /**
     * @brief Texture ID.
     */
    unsigned int texId = 0;

    /**
     * @brief Bitmap data for the texture.
     */
    unsigned char* bitmap = new unsigned char[256 * 256 * 3];

    // Add any other texture-related members here
};
