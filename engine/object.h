/**
 * @file	object.h
 * @brief	A simple object class
 *
 * This file contains the declaration of the Object class, a simple representation of an object.
 * It includes features for managing an object's ID, name, and rendering functionality.
 *
 * @author	Jari Näser (C) SUPSI [jari.naeser@student.supsi.ch]
 * @author  Carlo Pezzotti (C) SUPSI [carlo.pezzotti@student.supsi.ch]
 */

#pragma once

 //////////////
 // #INCLUDE //
 //////////////

#include <string>
#include <glm/glm.hpp>

#include "lib.h"

/////////////
// CLASSES //
/////////////

/**
 * @brief Simple object class example.
 */
class LIB_API Object {
	///////////
private: //
	///////////
	/**
	 * @brief ID of the object.
	 */
	unsigned int id;

	/**
	 * @brief Name of the object.
	 */
	std::string name;

	//////////
public: //
	//////////
	/**
	 * @brief Counter for generating unique IDs.
	 */
	static unsigned int idCounter;

	/**
	 * @brief Get the ID of the object.
	 * @return The ID of the object.
	 */
	unsigned int getId();

	/**
	 * @brief Set the ID of the object.
	 * @param id The new ID for the object.
	 */
	void setId(unsigned int id);

	/**
	 * @brief Get the name of the object.
	 * @return The name of the object.
	 */
	std::string getName();

	/**
	 * @brief Set the name of the object.
	 * @param name The new name for the object.
	 */
	void setName(std::string name);

	/**
	 * @brief Render function for the object.
	 *
	 * This function is a pure virtual function that must be implemented by derived classes.
	 *
	 * @param transform The transformation matrix for rendering the object.
	 * @param data Additional data for rendering (optional).
	 * @return A boolean indicating the success of the rendering operation.
	 */
	virtual bool render(glm::mat4 transform, void* data) = 0;

	/**
	 * @brief Get the next available ID.
	 * @return The next available ID.
	 */
	unsigned int getNextId();
};
