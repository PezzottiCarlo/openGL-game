/**
 * @file	material.h
 * @brief	Material class definition
 *
 * This file contains the declaration of the Material class, which represents a material used in rendering.
 * It inherits from the base Object class and includes properties such as emission, ambient, diffuse, specular,
 * shininess, and an optional texture.
 *
 * @author	Jari Näser (C) SUPSI [jari.naeser@student.supsi.ch]
 * @author  Carlo Pezzotti (C) SUPSI [carlo.pezzotti@student.supsi.ch]
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
class LIB_API Material : public Object {
    //////////
public: //
    //////////

    // Constructor
    /**
     * @brief Default constructor for the Material class.
     */
    Material();

    /**
     * @brief Constructor for the Material class with specified properties.
     *
     * @param name The name of the material.
     * @param _emission The emission color of the material.
     * @param _ambient The ambient color of the material.
     * @param _diffuse The diffuse color of the material.
     * @param _specular The specular color of the material.
     * @param _shininess The shininess coefficient of the material.
     */
    Material(const std::string name, glm::vec4 _emission, glm::vec4 _ambient, glm::vec4 _diffuse, glm::vec4 _specular, float _shininess);

    // Destructor
    /**
     * @brief Destructor for the Material class.
     */
    ~Material();

    // Setter
    /**
     * @brief Set the shininess coefficient of the material.
     * @param shininess The new shininess coefficient.
     */
    void setShininess(float shininess);

    /**
     * @brief Set the emission color of the material.
     * @param emission The new emission color.
     */
    void setEmission(glm::vec4 emission);

    /**
     * @brief Set the ambient color of the material.
     * @param ambient The new ambient color.
     */
    void setAmbient(glm::vec4 ambient);

    /**
     * @brief Set the diffuse color of the material.
     * @param diffuse The new diffuse color.
     */
    void setDiffuse(glm::vec4 diffuse);

    /**
     * @brief Set the specular color of the material.
     * @param specular The new specular color.
     */
    void setSpecular(glm::vec4 specular);

    /**
     * @brief Set the texture associated with the material.
     * @param texture The new texture.
     */
    void setTexture(Texture* texture);

    // Getter
    /**
     * @brief Get the emission color of the material.
     * @return The emission color.
     */
    glm::vec4 getEmission();

    /**
     * @brief Get the ambient color of the material.
     * @return The ambient color.
     */
    glm::vec4 getAmbient();

    /**
     * @brief Get the diffuse color of the material.
     * @return The diffuse color.
     */
    glm::vec4 getDiffuse();

    /**
     * @brief Get the specular color of the material.
     * @return The specular color.
     */
    glm::vec4 getSpecular();

    /**
     * @brief Get the shininess coefficient of the material.
     * @return The shininess coefficient.
     */
    float getShininess();

    /**
     * @brief Get the texture associated with the material.
     * @return The texture.
     */
    Texture* getTexture();

    // Other
    /**
     * @brief Render function for the material.
     *
     * This function renders the material based on the given transformation matrix.
     *
     * @param transform The transformation matrix for rendering the material.
     * @param data Additional data for rendering (optional).
     * @return A boolean indicating the success of the rendering operation.
     */
    virtual bool render(glm::mat4 transform, void* data) override;

    // Test method
    /**
     * @brief Perform a test operation for the Material class.
     * @return An integer indicating the result of the test.
     */
    static int test();

    ///////////
private: //
    ///////////

    // Material settings
    glm::vec4 emission;     ///< The emission color of the material.
    glm::vec4 ambient;      ///< The ambient color of the material.
    glm::vec4 diffuse;      ///< The diffuse color of the material.
    glm::vec4 specular;     ///< The specular color of the material.
    float shininess;        ///< The shininess coefficient of the material.
    Texture* texture;       ///< The texture associated with the material.
};
