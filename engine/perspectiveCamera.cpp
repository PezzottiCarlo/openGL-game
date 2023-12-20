/**
 * @file    perspectiveCamera.cpp
 * @brief   A simple perspectiveCamera class
 *
 * @author  Jari Näser (C) SUPSI [jari.naeser@student.supsi.ch]
 * @author  Carlo pezzotti (C) SUPSI [carlo.pezzotti@student.supsi.ch]
 */


 //////////////
 // #INCLUDE //
 //////////////

 // Library main include:
#include "perspectiveCamera.h"
#include "engine.h"

/////////////////////////////////////
// BODY OF CLASS PerspectiveCamera //
/////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * Method that returns the cameras perspective projection matrix
 * @return perspective projection matrix
 */
glm::mat4 LIB_API PerspectiveCamera::getPerspectiveProj() {
	return glm::mat4(1.0f);
}
