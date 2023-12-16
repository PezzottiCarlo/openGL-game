/**
 * @file	node.h
 * @brief	A simple node class
 *
 * @author	Jari Näser (C) SUPSI [jari.naeser@student.supsi.ch]
 * @author  Carlo pezzotti (C) SUPSI [carlo.pezzotti@student.supsi.ch]
 */

#pragma once


//////////////
// #INCLUDE //
//////////////

#include "object.h"
#include "engine.h"
#include <vector>


/////////////
// CLASSES //
/////////////

/**
 * @brief Simple node class.
 */
class LIB_API Node : public Object{

	///////////
	private: //
	///////////
		glm::mat4 transform = glm::mat4(1.0f);
		std::vector<Node*> children;	
		Node* parent;
		

	//////////
	public: //
	//////////
		// Constructor
		Node(std::string name);
		~Node();
		// Matrix
		glm::mat4 getTransform() const;
		virtual void setTransform(glm::mat4 transform);
		glm::mat4 getFinalMatrix() const;

		glm::vec3 getWorldPosition() const;
		virtual void setWorldPosition(glm::vec3 position);

		// Children
		bool addChild(Node*);
		bool removeChild(Node*);
		std::vector<Node*> getChildren();
		void setChildren(std::vector<Node*>);
		int getNumberOfChildren();

		// Parent
		Node* getParent();
		void setParent(Node*);

		// Other
		virtual bool render(glm::mat4, void*) override;

		// Test method
		static int test();
};

