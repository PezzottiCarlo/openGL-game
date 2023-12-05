/**
 * @file	object.h
 * @brief	A simple object class
 *
 * @author	Jari Näser (C) SUPSI [jari.naeser@student.supsi.ch]
 * @author  Carlo pezzotti (C) SUPSI [carlo.pezzotti@student.supsi.ch]
 */

#pragma once


//////////////
// #INCLUDE //
//////////////

#include <string>
#include <glm.hpp>
#include "engine.h"

/////////////
// CLASSES //
/////////////

/**
 * @brief Simple object class example.
 */
class LIB_API Object{

	///////////
	private: //
	///////////
		unsigned int id;
		std::string name;

	//////////
	public: //
	//////////
		unsigned int getId();
		void setId(unsigned int);
		std::string getName();
		void setName(std::string);
		virtual bool render(glm::mat4, void*) = 0;
};
