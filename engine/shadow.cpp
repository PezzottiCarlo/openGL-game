#include "shadow.h"

LIB_API Shadow::Shadow(std::string name) : Node(name)
{
}

LIB_API Shadow::~Shadow()
{
}

void Shadow::addVertex(Vertex* v)
{

}

std::vector<Vertex*> Shadow::getVertices()
{
	return vertices;
}

bool LIB_API Shadow::render(glm::mat4, void*)
{
	return false;
}

float Shadow::getDeepestPoint()
{
	return 0.0f;
}
