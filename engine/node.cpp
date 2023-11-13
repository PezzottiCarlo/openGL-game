/**
 * @file    node.cpp
 * @brief   A simple node class
 *
 * @author  Jari Näser (C) SUPSI [jari.naeser@student.supsi.ch]
 * @author  Carlo pezzotti (C) SUPSI [carlo.pezzotti@student.supsi.ch]
 */


//////////////
// #INCLUDE //
//////////////

// Library main include:
#include "node.h"
#include "engine.h"
#include <iostream>
#include <random>
#include <chrono>

////////////////////////
// BODY OF CLASS Node //
////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * Constructor of node class
 * @param name name of the node object
 */
Node::Node(std::string name) {
	// Generate random number
	auto now = std::chrono::system_clock::now();
	auto seed = now.time_since_epoch().count();

	std::mt19937 gen(static_cast<unsigned>(seed));
	std::uniform_int_distribution<int> distribution(100000, 999999);

	// Set id
	setId(distribution(gen));

	// Set name
	Object::setName(name);

	// Set matrix
	matrix = glm::mat4(1.0f);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * Destructor of node class
 */
Node::~Node() {

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * Getter of matrix attribute
 * @return value of the name attribute
 */
glm::mat4 LIB_API Node::getMatrix() {
	return matrix;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * Setter of the matrix structure
 * @param newMatrix New matrix
 */
void LIB_API Node::setMatrix(glm::mat4 newMatrix) {
	matrix = newMatrix;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * Adds a given node to the children vector
 * @param nodeToAdd Node to add
 * @return true if operation has been completed without any errors.
 */
bool LIB_API Node::addChild(Node* nodeToAdd) {
	children.push_back(nodeToAdd);
	return true;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * Removes a given node from the children vector 
 * @param nodeToRemove Node to remove
 * @return true if operation has been completed without any errors (also if node has not been found). 
 */
bool LIB_API Node::removeChild(Node* nodeToRemove) {
	children.erase(
		std::remove(children.begin(), children.end(), nodeToRemove), 
		children.end()
	);
	return true;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * Getter of the children vector
 * @return children vector
 */
std::vector<Node*> LIB_API Node::getChildren() {
	return children;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * Setter of the children structure
 * @param newChildren New children vector
 */
void LIB_API Node::setChildren(std::vector<Node*> newChildren) {
	children = newChildren;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * Getter of the parent node
 * @return Parent node
 */
Node* Node::getParent() {
	return parent;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * Setter of the parent node
 * @param newParent New parent node
 */
void LIB_API Node::setParent(Node* newParent) {
	parent = newParent;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * Getter of the worldCoordinates matrix
 * @return Matrix that represents world coordinates
 */
glm::mat4 LIB_API Node::getWorldCoordinatesMat() {

	// TO BE IMPLEMENTED

	return glm::mat4(0);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * Render method that renders a given object through its matrix
 * @param mat matrix
 * @param attr additional attributes
 */
bool LIB_API Node::render(glm::mat4 mat, void* attr) {
	return false;
}