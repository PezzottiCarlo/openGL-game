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
#include "texture.h"

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
    Material(const std::string name, glm::vec4 _emission, glm::vec4 _ambient, glm::vec4 _diffuse, glm::vec4 _specular, float _shininess);

    // Destructor
    ~Material();

    // Setter
    void setShininess(float shininess);
    void setEmission(glm::vec4 emission);
    void setAmbient(glm::vec4 ambient);
    void setDiffuse(glm::vec4 diffuse);
    void setSpecular(glm::vec4 specular);
    void setTexture(Texture* texture);

    // Getter
    glm::vec4 getEmission();
    glm::vec4 getAmbient();
    glm::vec4 getDiffuse();
    glm::vec4 getSpecular();
    float getShininess();
    Texture* getTexture();

    // Other
    virtual bool render(glm::mat4, void*) override;
    // Test method
    static int test();

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
    Texture* texture;
};