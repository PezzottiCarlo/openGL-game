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
#include <gl/freeglut.h>


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

public:
    enum LightType
    {
        DIRECTIONAL,
        POINT,
        SPOT
    };
    // Set light properties
    void setIntensity(float intensity);
    // Get light intensity
    float getIntensity();
    // Color is a float array with 3 components (RGB) from 0 to 1
    void setColor(float r, float g, float b);
    // get Color
    float* getColor();
    // Set light type
    void setLightType(LightType type);
    // get lightType
    LightType getLightType();
    // Set light position
    void setPosition();
    // Set light position
    void setPosition(glm::vec4 pos);
    // Get light position
    glm::vec4 getPosition();
    // Override render method
    virtual bool render(glm::mat4, void*) override;
///////////
private: //
///////////
    // Light settings
    float intensity;
    // Color is a float array with 3 components (RGB) from 0 to 1
    float color[3]; // RGB color components
    // Light type
    LightType type = DIRECTIONAL;
    // Light position
    glm::vec4 position;
    // Light number
    int lightNumber = GL_LIGHT0;
};

