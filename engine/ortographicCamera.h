/**
 * @file	ortographicCamera.h
 * @brief	A simple OrtographicCamera class
 *
 * @author	Jari Näser (C) SUPSI [jari.naeser@student.supsi.ch]
 * @author  Carlo pezzotti (C) SUPSI [carlo.pezzotti@student.supsi.ch]
 */

#pragma once


 //////////////
 // #INCLUDE //
 //////////////

#include "camera.h"
#include "engine.h"



/////////////
// CLASSES //
/////////////

/**
 * @brief Simple ortographicCamera class.
 */
class LIB_API OrtographicCamera : public Camera {
	//////////
	public: //
	//////////
		glm::mat4 getOrtographicProj();
};

