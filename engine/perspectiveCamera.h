/**
 * @file	perspectiveCamera.h
 * @brief	A simple PerspectiveCamera class
 *
 * @author	Jari Näser (C) SUPSI [jari.naeser@student.supsi.ch]
 * @author  Carlo pezzotti (C) SUPSI [carlo.pezzotti@student.supsi.ch]
 */

#pragma once


 //////////////
 // #INCLUDE //
 //////////////

#include "camera.h"




/////////////
// CLASSES //
/////////////

/**
 * @brief Simple perspectiveCamera class.
 */
class LIB_API PerspectiveCamera : public Camera {
	//////////
	public: //
	//////////
		glm::mat4 getPerspectiveProj();
};

