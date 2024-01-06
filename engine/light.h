/**
 * @file	Light.h
 * @brief	Definition of the Light class.
 *
 * This file contains the declaration of the Light class, which represents a light source in a scene.
 * It inherits from the base Node class and serves as a base class for different types of lights.
 *
 * @author	Jari Näser (C) SUPSI [jari.naeser@student.supsi.ch]
 * @author  [Carlo Pezzotti (C) SUPSI [carlo.pezzotti@student.supsi.ch]
 */

#ifndef LIGHT
#define LIGHT

#include "lib.h"
#include "node.h"

 /**
  * @brief Light class.
  *
  * This class represents a light source in a scene. It inherits from the base Node class.
  */
class LIB_API Light : public Node {

public:
    /**
     * @brief Constructor for the Light class.
     *
     * @param name The name of the light.
     * @param lightNumber The light number associated with the light.
     * @param ambient The ambient color of the light.
     * @param diffuse The diffuse color of the light.
     * @param specular The specular color of the light.
     */
    Light(const std::string name, const int lightNumber, const glm::vec4 ambient, const glm::vec4 diffuse, const glm::vec4 specular);

    /**
     * @brief Destructor for the Light class.
     */
    ~Light();

public:
    /**
     * @brief Get the light number associated with the light.
     * @return The light number.
     */
    int getLightNumber();

    /**
     * @brief Set the position of the light.
     */
    void setPosition();

    /**
     * @brief Set the position of the light.
     * @param pos The new position of the light.
     */
    void setPosition(glm::vec4 pos);

    /**
     * @brief Get the position of the light.
     * @return The position of the light.
     */
    glm::vec4 getPosition();

    /**
     * @brief Get the constant attenuation coefficient of the light.
     * @return The constant attenuation coefficient.
     */
    float getConstantAttenuation();

    /**
     * @brief Get the linear attenuation coefficient of the light.
     * @return The linear attenuation coefficient.
     */
    float getLinearAttenuation();

    /**
     * @brief Get the quadratic attenuation coefficient of the light.
     * @return The quadratic attenuation coefficient.
     */
    float getQuadraticAttenuation();

    /**
     * @brief Set the constant attenuation coefficient of the light.
     * @param constantAttenuation The new constant attenuation coefficient.
     */
    void setConstantAttenuation(float constantAttenuation);

    /**
     * @brief Set the linear attenuation coefficient of the light.
     * @param linearAttenuation The new linear attenuation coefficient.
     */
    void setLinearAttenuation(float linearAttenuation);

    /**
     * @brief Set the quadratic attenuation coefficient of the light.
     * @param quadraticAttenuation The new quadratic attenuation coefficient.
     */
    void setQuadraticAttenuation(float quadraticAttenuation);

    /**
     * @brief Set the intensity of the light.
     * @param intensity The new intensity of the light.
     */
    void setIntensity(float intensity);

    /**
     * @brief Get the next available light number.
     * @return The next available light number.
     */
    static int getNextLightNumber();

    /**
     * @brief Render function for the light.
     *
     * This function renders the light based on the given transformation matrix.
     *
     * @param transform The transformation matrix for rendering the light.
     * @param data Additional data for rendering (optional).
     * @return A boolean indicating the success of the rendering operation.
     */
    virtual bool render(glm::mat4 transform, void* data) override;

    /**
     * @brief Set the transformation matrix for the light.
     *
     * @param transform The new transformation matrix for the light.
     */
    virtual void setTransform(glm::mat4 transform) override;

    /**
     * @brief Perform a test operation for the Light class.
     * @return An integer indicating the result of the test.
     */
    static int test();

private:
    static int nextNumber;  ///< Static variable to track the next available light number.
    int lightNumber;        ///< The light number associated with the light.
    glm::vec4 ambient;      ///< The ambient color of the light.
    glm::vec4 diffuse;      ///< The diffuse color of the light.
    glm::vec4 specular;     ///< The specular color of the light.
    glm::vec4 position{ 0.0f, 0.0f, 0.0f, 1.0f };  ///< The position of the light.

    float constantAttenuation = 1.0f;   ///< The constant attenuation coefficient of the light.
    float linearAttenuation = 0.0f;     ///< The linear attenuation coefficient of the light.
    float quadraticAttenuation = 0.0f;  ///< The quadratic attenuation coefficient of the light.
    float intensity = 7.0f;             ///< The intensity of the light.
};

#endif
