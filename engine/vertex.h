/**
 * @file    vertex.h
 * @brief   Vertex class definition
 *
 * This file contains the declaration of the Vertex class, representing a 3D vertex with position, normal, and texture coordinates.
 *
 * @author  Jari Näser (C) SUPSI [jari.naeser@student.supsi.ch]
 * @author  Carlo Pezzotti (C) SUPSI [carlo.pezzotti@student.supsi.ch]
 */

#pragma once

#include "lib.h"
#include <glm/glm.hpp>

 /**
  * @brief Vertex class.
  */
class LIB_API Vertex {

public:
    /**
     * @brief Constructor for Vertex.
     *
     * @param position The 3D position of the vertex.
     * @param normal The normal vector of the vertex.
     */
    Vertex(glm::vec3 position, glm::vec3 normal);

    /**
     * @brief Destructor for Vertex.
     */
    ~Vertex();

public:
    /**
     * @brief Get the 3D position of the vertex.
     *
     * @return The 3D position of the vertex.
     */
    glm::vec3 getPosition();

    /**
     * @brief Get the normal vector of the vertex.
     *
     * @return The normal vector of the vertex.
     */
    glm::vec3 getNormal();

    /**
     * @brief Get the texture coordinates of the vertex.
     *
     * @return The texture coordinates of the vertex.
     */
    glm::vec2 getTextureCoordinates();

    /**
     * @brief Set the texture coordinates of the vertex.
     *
     * @param textCoord The texture coordinates to set.
     */
    void setTextureCoordinates(glm::vec2 textCoord);

private:
    /**
     * @brief 3D position of the vertex.
     */
    glm::vec3 position;

    /**
     * @brief Normal vector of the vertex.
     */
    glm::vec3 normal;

    /**
     * @brief Texture coordinates of the vertex.
     */
    glm::vec2 textureCoordinates;

};
