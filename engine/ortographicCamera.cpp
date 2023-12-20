/**
 * @file    ortographicCamera.cpp
 * @brief   A simple ortographicCamera class
 *
 * @author  Jari Näser (C) SUPSI [jari.naeser@student.supsi.ch]
 * @author  Carlo pezzotti (C) SUPSI [carlo.pezzotti@student.supsi.ch]
 */


 //////////////
 // #INCLUDE //
 //////////////

 // Library main include:
#include "ortographicCamera.h"
#include "engine.h"

/////////////////////////////////////
// BODY OF CLASS OrtographicCamera //
/////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * Method that returns the cameras ortographic projection matrix
 * @return ortographic projection matrix
 */
glm::mat4 LIB_API OrtographicCamera::getOrtographicProj() {
	return glm::mat4(1.0f);
}

