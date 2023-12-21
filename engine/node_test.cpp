#include "node.h"

int Node::test() { 

	Node node("TestNode");
	Node child1Node("Child1Node");
	Node child2Node("Child2Node");

	// test addChild
	assert(node.getChildren().size() == 0);
	
	node.addChild(&child1Node);
	node.addChild(&child2Node);

	assert(node.getChildren().size() == 2);

	// test removeChild
	assert(node.getChildren().size() == 2);
	node.removeChild(&child2Node);
	assert(node.getChildren().size() == 1);

	// test getParent
	assert(child1Node.getParent() == &node);
	child1Node.setParent(&child2Node);
	assert(child1Node.getParent() == &child2Node);

	return 0;
}