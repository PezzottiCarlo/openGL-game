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

 // Library main include:
#include "camera.h"
#include "engine.h"

//////////////////////////
// BODY OF CLASS Camera //
//////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * Method that returns the inverse of the camera matrix
 * @return inversed camera matrix
 */
glm::mat4 LIB_API Camera::getInverseCameraMat() {
	return glm::inverse(getMatrix());
}