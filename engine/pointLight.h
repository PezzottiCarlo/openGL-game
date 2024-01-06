/**
 * @file	pointlight.h
 * @brief	PointLight class definition
 *
 * This file contains the declaration of the PointLight class, which is a derived class from the Light class.
 * It represents a point light source with additional properties such as cut-off angle.
 *
 * @author	Jari Näser (C) SUPSI [jari.naeser@student.supsi.ch]
 * @author  Carlo Pezzotti (C) SUPSI [carlo.pezzotti@student.supsi.ch]
 */

#ifndef POINT_LIGHT
#define POINT_LIGHT

#include "lib.h"
#include "light.h"

 /**
  * @brief PointLight class derived from the Light class.
  */
class LIB_API PointLight : public Light {

public:
    /**
     * @brief Constructor for PointLight.
     *
     * @param name The name of the point light.
     * @param lightNumber The light number associated with the point light.
     * @param ambient The ambient color of the point light.
     * @param diffuse The diffuse color of the point light.
     * @param specular The specular color of the point light.
     * @param cutOff The cut-off angle for the point light (default is 180 degrees).
     */
    PointLight(const std::string name, const int lightNumber, const glm::vec4 ambient, const glm::vec4 diffuse, const glm::vec4 specular, const float cutOff = 180.0f);

    /**
     * @brief Destructor for PointLight.
     */
    ~PointLight() {};

public:
    /**
     * @brief Render function for the point light.
     *
     * @param transform The transformation matrix for rendering the point light.
     * @param data Additional data for rendering (optional).
     * @return A boolean indicating the success of the rendering operation.
     */
    virtual bool render(glm::mat4 transform, void* data) override;

private:
    /**
     * @brief Cut-off angle for the point light.
     */
    float cutOff;
};

#endif
