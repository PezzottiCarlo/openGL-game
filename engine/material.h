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

    // Setter
    void setShininess(float shininess);
    void setEmission(glm::vec4 emission);
    void setAmbient(glm::vec4 ambient);
    void setDiffuse(glm::vec4 diffuse);
    void setSpecular(glm::vec4 specular);
    // Getter
    glm::vec4 getEmission();
    glm::vec4 getAmbient();
    glm::vec4 getDiffuse();
    glm::vec4 getSpecular();
    float getShininess();

    // Other
    virtual bool render(glm::mat4, void*) override;

///////////
private: //
///////////
    // Material settings
    std::string diffuseTexturePath;
    glm::vec4 emission;
    glm::vec4 ambient;
    glm::vec4 diffuse;
    glm::vec4 specular;
    float shininess;
    // Add any other material-related members here
};