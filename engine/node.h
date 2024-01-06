/**
 * @file	node.h
 * @brief	A simple node class
 *
 * This file contains the declaration of the Node class, a simple node representation.
 * It inherits from the base Object class and includes features for managing transformations,
 * hierarchy, and rendering.
 *
 * @author	Jari Näser (C) SUPSI [jari.naeser@student.supsi.ch]
 * @author  Carlo Pezzotti (C) SUPSI [carlo.pezzotti@student.supsi.ch]
 */

#pragma once

 //////////////
 // #INCLUDE //
 //////////////
#include <vector>
#include "object.h"

/////////////
// CLASSES //
/////////////

/**
 * @brief Simple node class.
 */
class LIB_API Node : public Object {
	//////////
public: //
	//////////
	/**
	 * @brief Constructor for the Node class.
	 * @param name The name of the node.
	 */
	Node(std::string name);

	/**
	 * @brief Destructor for the Node class.
	 */
	~Node();

	/**
	 * @brief Get the transformation matrix of the node.
	 * @return The transformation matrix.
	 */
	glm::mat4 getTransform() const;

	/**
	 * @brief Set the transformation matrix of the node.
	 * @param transform The new transformation matrix.
	 */
	virtual void setTransform(glm::mat4 transform);

	/**
	 * @brief Get the final transformation matrix of the node.
	 * @return The final transformation matrix.
	 */
	glm::mat4 getFinalMatrix() const;

	/**
	 * @brief Get the child node at a specific index.
	 * @param index The index of the child node.
	 * @return The child node at the specified index.
	 */
	Node* getChildAt(int index);

	/**
	 * @brief Get the world position of the node.
	 * @return The world position of the node.
	 */
	glm::vec3 getWorldPosition() const;

	/**
	 * @brief Set the world position of the node.
	 * @param position The new world position.
	 */
	virtual void setWorldPosition(glm::vec3 position);

	/**
	 * @brief Add a child node to the node.
	 * @param child The child node to add.
	 * @return A boolean indicating the success of adding the child.
	 */
	bool addChild(Node* child);

	/**
	 * @brief Remove a child node from the node.
	 * @param child The child node to remove.
	 * @return A boolean indicating the success of removing the child.
	 */
	bool removeChild(Node* child);

	/**
	 * @brief Get the vector of child nodes.
	 * @return The vector of child nodes.
	 */
	std::vector<Node*> getChildren();

	/**
	 * @brief Set the vector of child nodes.
	 * @param children The new vector of child nodes.
	 */
	void setChildren(std::vector<Node*> children);

	/**
	 * @brief Get the number of child nodes.
	 * @return The number of child nodes.
	 */
	unsigned int getNumberOfChildren();

	/**
	 * @brief Get the parent node.
	 * @return The parent node.
	 */
	Node* getParent();

	/**
	 * @brief Set the parent node.
	 * @param parent The new parent node.
	 */
	void setParent(Node* parent);

	/**
	 * @brief Render function for the node.
	 *
	 * This function renders the node based on the given transformation matrix.
	 *
	 * @param transform The transformation matrix for rendering the node.
	 * @param data Additional data for rendering (optional).
	 * @return A boolean indicating the success of the rendering operation.
	 */
	virtual bool render(glm::mat4 transform, void* data) override;

	/**
	 * @brief Set the scale factor of the node.
	 * @param scale The new scale factor.
	 */
	void setScale(float scale);

	/**
	 * @brief Get the scale factor of the node.
	 * @return The scale factor.
	 */
	float getScale() const;

	/**
	 * @brief Test method for the Node class.
	 * @return An integer indicating the result of the test.
	 */
	static int test();

	///////////
private: //
	///////////
	glm::mat4 transform = glm::mat4(1.0f);  ///< The transformation matrix of the node.
	std::vector<Node*> children;            ///< The vector of child nodes.
	Node* parent;                           ///< The parent node.
	float scale;                            ///< The scale factor of the node.
};
