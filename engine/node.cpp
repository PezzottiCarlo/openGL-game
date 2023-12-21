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
#include <algorithm>

////////////////////////
// BODY OF CLASS Node //
////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * Constructor of node class
 * @param name name of the node object
 */
Node::Node(std::string name) {
	Object::setId(Object::getNextId());
	Object::setName(name);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * Destructor of node class
 */
Node::~Node() {

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * Adds a given node to the children vector
 * @param nodeToAdd Node to add
 * @return true if operation has been completed without any errors.
 */
bool LIB_API Node::addChild(Node* nodeToAdd) {
	nodeToAdd->setParent(this);
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
	auto child = std::find(children.begin(), children.end(), nodeToRemove);
	if (child != children.end()) {
		delete* child;
		children.erase(child);
		return true;
	}
	return false;
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
 * Render method that renders a given object through its matrix
 * @param mat matrix
 * @param attr additional attributes
 * @return false value
 */
bool LIB_API Node::render(glm::mat4 mat, void* attr) {
	return false;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * Getter of the transform matrix
 * @return transform matrix
 */
glm::mat4 LIB_API Node::getTransform() const
{
	return transform;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * Setter of the transform matrix
 * @param transform New transform matrix
 */
void LIB_API Node::setTransform(glm::mat4 transform)
{
	Node::transform = transform;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * Getter of the final matrix, which is the matrix of the node multiplied by the matrices of its parents
 * @return final matrix
 */
glm::mat4 LIB_API Node::getFinalMatrix() const {

	Node* par = parent;
	std::vector<Node*> parents;
	while (par != nullptr) {
		parents.push_back(par);
		par = par->getParent();
	}

	glm::mat4 m = glm::mat4(1.0f);
	for (int i = parents.size() - 1; i >= 0; i--) {
		par = parents.at(i);
		m *= par->getTransform();
	}
	m *= transform;

	return m;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * Getter of the world position of the node
 * @return world position
 */
glm::vec3 LIB_API Node::getWorldPosition() const {
	return glm::vec3(getFinalMatrix()[3]);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * Setter of the world position of the node
 * @param position New world position
 */
void LIB_API Node::setWorldPosition(glm::vec3 position) {
	transform[3] = glm::vec4(position, 1.0f);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * Returns the number of children
 * @return Number of children
 */
int LIB_API Node::getNumberOfChildren() {
	return getChildren().size();
}

Node* Node::getChildAt(int index) {
	if (children.empty() || index >= (int)children.size())
		return nullptr;

	return children.at(index);//.get();
}