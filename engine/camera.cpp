/**
 * @file    camera.cpp
 * @brief   A simple camera class
 *
 * @author  Jari Näser (C) SUPSI [jari.naeser@student.supsi.ch]
 * @author  Carlo pezzotti (C) SUPSI [carlo.pezzotti@student.supsi.ch]
 */

 //////////////
 // #INCLUDE //
 //////////////

#include "camera.h"
#include <glm/ext/matrix_transform.hpp>

Camera::~Camera() {
}

glm::mat4 LIB_API Camera::getInverseCameraMat() {
	// Returns inverse of a node's transform matrix
	return glm::inverse(getTransform());
}

void Camera::setUserTransform(float x, float y, float z, float rx, float ry, float rz)
{
	glm::mat4 t = glm::translate(glm::mat4(1.0f), glm::vec3(x, y, z));
	t = glm::rotate(t, glm::radians(rx), glm::vec3(1.0f, 0.0f, 0.0f));
	t = glm::rotate(t, glm::radians(ry), glm::vec3(0.0f, 1.0f, 0.0f));
	t = glm::rotate(t, glm::radians(rz), glm::vec3(0.0f, 0.0f, 1.0f));
	setTransform(t);
}
