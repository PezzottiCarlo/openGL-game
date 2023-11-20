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
		glm::mat4 matrix;
		std::vector<Node*> children;	
		Node* parent;
		

	//////////
	public: //
	//////////
		// Constructor
		Node(std::string name);
		~Node();
		// Matrix
		glm::mat4 getMatrix();
		void setMatrix(glm::mat4);

		// Children
		bool addChild(Node*);
		bool removeChild(Node*);
		std::vector<Node*> getChildren();
		void setChildren(std::vector<Node*>);

		// Parent
		Node* getParent();
		void setParent(Node*);

		// Other
		glm::mat4 getWorldCoordinatesMat();
		virtual bool render(glm::mat4, void*);
};

