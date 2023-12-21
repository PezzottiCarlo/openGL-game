#include "object.h"
#include "node.h"
#include <list>

#ifndef LIST
#define LIST

class LIB_API List : public  Object {
public:
	List() {}
	void addEntry(Node*);
	bool render(glm::mat4,void*) override;
	void clear();
	Node* getObject(int);
	int size();

private:
	std::list<Node*> objectsList;
};

#endif