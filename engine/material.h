/**
 * @file	material.h
 * @brief	Material class definition
 *
 * @author	Jari Näser (C) SUPSI [jari.naeser@student.supsi.ch]
 * @author  Carlo pezzotti (C) SUPSI [carlo.pezzotti@student.supsi.ch]
 */

#pragma once

 /////////////
 // #INCLUDE //
 /////////////

#include <string>     // Include for std::string
#include "object.h"  

/////////////
// CLASSES //
/////////////

/**
 * @brief Material class
 */
class LIB_API Material : public Object{
//////////
public: //
//////////

    // Constructor
    Material(const std::string name);

    // Destructor
    ~Material();

    // Set material settings
    void setMaterialSettings(const std::string& diffuseTexturePath, float shininess);

    // Render the material
    void render();

///////////
private: //
///////////
    // Material settings
    std::string diffuseTexturePath;
    float shininess;
    // Add any other material-related members here
};