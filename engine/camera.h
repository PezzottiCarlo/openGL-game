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
class LIB_API Camera : public Node{
	//////////
	public: //
	//////////
		glm::mat4 getInverseCameraMat();
};

