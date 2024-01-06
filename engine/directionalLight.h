/**
 * @file	DirectionalLight.h
 * @brief	Definition of the DirectionalLight class.
 *
 * This file contains the declaration of the DirectionalLight class,
 * which represents a directional light source in a scene. It inherits
 * from the base Light class.
 *
 * @author	Jari Näser (C) SUPSI [jari.naeser@student.supsi.ch]
 * @author  Carlo Pezzotti (C) SUPSI [carlo.pezzotti@student.supsi.ch]
 */

#ifndef DIRECTIONAL_LIGHT
#define DIRECTIONAL_LIGHT

#include "light.h"

 /**
  * @brief Directional Light class.
  *
  * This class represents a directional light source in a scene.
  * It inherits from the base Light class.
  */
class LIB_API DirectionalLight : public Light {

public:
    /**
     * @brief Constructor for the DirectionalLight class.
     *
     * @param name The name of the directional light.
     * @param lightNumber The light number associated with the directional light.
     * @param ambient The ambient color of the directional light.
     * @param diffuse The diffuse color of the directional light.
     * @param specular The specular color of the directional light.
     */
    DirectionalLight(const std::string name, const int lightNumber, const glm::vec4 ambient, const glm::vec4 diffuse, const glm::vec4 specular);

    /**
     * @brief Destructor for the DirectionalLight class.
     */
    ~DirectionalLight() {};

public:
    /**
     * @brief Render function for the directional light.
     *
     * This function renders the directional light based on the given transformation matrix.
     *
     * @param transform The transformation matrix for rendering the light.
     * @param data Additional data for rendering (optional).
     * @return A boolean indicating the success of the rendering operation.
     */
    bool render(glm::mat4 transform, void* data) override;

    /**
     * @brief Set the transformation matrix for the directional light.
     *
     * @param transform The new transformation matrix for the directional light.
     */
    void setTransform(glm::mat4 transform) override;
};

#endif
