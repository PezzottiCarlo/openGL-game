/**
 * @file    spotlight.h
 * @brief   SpotLight class definition
 *
 * This file contains the declaration of the SpotLight class, which is a derived class from the PointLight class.
 * It represents a spot light source with additional properties such as direction.
 *
 * @author  Jari Näser (C) SUPSI [jari.naeser@student.supsi.ch]
 * @author  Carlo Pezzotti (C) SUPSI [carlo.pezzotti@student.supsi.ch]
 */

#ifndef SPOT_LIGHT
#define SPOT_LIGHT

#include "lib.h"
#include "pointLight.h"

 /**
  * @brief SpotLight class derived from the PointLight class.
  */
class LIB_API SpotLight : public PointLight {

public:
    /**
     * @brief Constructor for SpotLight.
     *
     * @param name The name of the spot light.
     * @param lightNumber The light number associated with the spot light.
     * @param ambient The ambient color of the spot light.
     * @param diffuse The diffuse color of the spot light.
     * @param specular The specular color of the spot light.
     * @param cutOff The cut-off angle for the spot light.
     * @param direction The direction of the spot light.
     */
    SpotLight(const std::string name, const int lightNumber, const glm::vec4 ambient,
        const glm::vec4 diffuse, const glm::vec4 specular, const float cutOff, const glm::vec3 direction);

    /**
     * @brief Destructor for SpotLight.
     */
    ~SpotLight() {};

public:
    /**
     * @brief Render function for the spot light.
     *
     * @param transform The transformation matrix for rendering the spot light.
     * @param data Additional data for rendering (optional).
     * @return A boolean indicating the success of the rendering operation.
     */
    bool render(glm::mat4 transform, void* data) override;

private:
    /**
     * @brief Direction of the spot light.
     */
    glm::vec3 direction;
};

#endif
