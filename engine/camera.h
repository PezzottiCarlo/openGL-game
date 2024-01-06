/**
 * @file	camera.h
 * @brief	A simple camera class
 *
 * @author	Jari Näser (C) SUPSI [jari.naeser@student.supsi.ch]
 * @author  Carlo pezzotti (C) SUPSI [carlo.pezzotti@student.supsi.ch]
 */

#pragma once

 //////////////
 // #INCLUDE //
 //////////////

#include "lib.h"
#include "node.h"

/////////////
// CLASSES //
/////////////

/**
 * @brief Simple camera class.
 */
class LIB_API Camera : public Node {
    //////////
public: //
    //////////

    /**
     * @brief Constructor for the Camera class.
     * @param name The name of the camera.
     */
    Camera(std::string name) : Node(name) {};

    /**
     * @brief Destructor for the Camera class.
     */
    ~Camera();

    /**
     * @brief Get the inverse transformation matrix of the camera.
     * @return The inverse camera matrix.
     */
    glm::mat4 getInverseCameraMat();

    /**
     * @brief Set user-defined transformation for the camera.
     * @param x Translation along the x-axis.
     * @param y Translation along the y-axis.
     * @param z Translation along the z-axis.
     * @param rx Rotation around the x-axis (in degrees).
     * @param ry Rotation around the y-axis (in degrees).
     * @param rz Rotation around the z-axis (in degrees).
     */
    void setUserTransform(float x, float y, float z, float rx, float ry, float rz);
};
