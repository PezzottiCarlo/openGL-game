/**
 * @file	light.h
 * @brief	Class light extends mesh
 *
 * @author	Jari Näser (C) SUPSI [jari.naeser@student.supsi.ch]
 * @author  Carlo pezzotti (C) SUPSI [carlo.pezzotti@student.supsi.ch]
 */

#pragma once


 //////////////
 // #INCLUDE //
 //////////////
#include "node.h"
#include "engine.h"


/////////////
// CLASSES //
/////////////

/**
 * @brief Simple mesh class.
 */
//create class light
class LIB_API Light : public Node {
//////////
public: //
//////////
    // Constructor
    Light(const std::string& name);

    // Destructor
    ~Light();

    // Set light properties
    void setIntensity(float intensity);
    void setColor(float r, float g, float b);

    // Render the light
    void render();

///////////
private: //
///////////
    // Light settings
    float intensity;
    float color[3]; // RGB color components
};

