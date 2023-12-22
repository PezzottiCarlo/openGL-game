/**
 * @file    object.cpp
 * @brief   A simple graphical engine library
 *
 * @author  Jari Näser (C) SUPSI [jari.naeser@student.supsi.ch]
 * @author  Carlo pezzotti (C) SUPSI [carlo.pezzotti@student.supsi.ch]
 */


//////////////
// #INCLUDE //
//////////////

// Library main include:
#include "object.h"

//////////////////////////
// BODY OF CLASS Object //
//////////////////////////

// Definition of static member outside the class
unsigned int Object::idCounter = 1;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * Getter of id attribute
 * @return value of the id attribute
 */
unsigned int Object::getId() {
	return id;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * Setter of id attribute
 * @param newId new id to assign
 */
void Object::setId(unsigned int newId) {
	id = newId;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * Getter of name attribute
 * @return value of the name attribute
 */
std::string LIB_API Object::getName(){
	return name;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * Setter of name attribute
 * @param newName new name to assign to name attribute
 */
void LIB_API Object::setName(std::string newName) {
	name = newName;
}

unsigned int LIB_API Object::getNextId() {
	idCounter++;
	return idCounter;
}