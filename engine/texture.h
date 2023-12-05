/**
 * @file	texture.h
 * @brief	Texture class definition
 *
 * @author	Jari Näser (C) SUPSI [jari.naeser@student.supsi.ch]
 * @author  Carlo pezzotti (C) SUPSI [carlo.pezzotti@student.supsi.ch]
 */

#pragma once

 /////////////
 // #INCLUDE //
 /////////////

#include "object.h"  // Assuming you have an "object.h" header for the base class
#include <string>     // Include for std::string

/////////////
// CLASSES //
/////////////

/**
 * @brief Texture class, extends Object
 */
class LIB_API Texture : public Object {
//////////
public: //
//////////
    // Constructor
    Texture(const std::string& name);

    // Destructor
    ~Texture();

    // Load texture from a file
    bool loadFromFile(const std::string& filePath);

    // Set texture settings (hypothetical example)
    void setTextureSettings(int width, int height, bool seamless);

    virtual bool render(glm::mat4, void*) override;
///////////
private: //
///////////
    // Texture-specific members
    std::string filePath;
    int width;
    int height;
    bool seamless;
    // Add any other texture-related members here
};