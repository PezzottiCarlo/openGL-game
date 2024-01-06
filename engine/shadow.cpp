#include "shadow.h"
#include <glm/gtc/type_ptr.hpp>


LIB_API Shadow::Shadow(Mesh* mesh):Node("ShadowOf"+mesh->getName())
{
	meshToShadow = mesh;
	for (Vertex* v : mesh->getVertices(0)) {
		addVertex(v);
	}
}

LIB_API Shadow::~Shadow(){}

void Shadow::addVertex(Vertex* v)
{
	float deepestPoint = getDeepestPoint();
	glm::vec3 position = v->getPosition();
	position.y = deepestPoint+1.0f;
	Vertex* projectedVertex = new Vertex(position, v->getNormal());
	vertices.push_back(projectedVertex);
}

std::vector<Vertex*> Shadow::getVertices()
{
	return vertices;
}

bool LIB_API Shadow::render(glm::mat4, void*)
{
	//create a shadow material
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_DEPTH_TEST);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, glm::value_ptr(glm::vec4(0.0f, 0.0f, 0.0f, 0.1f)));
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, glm::value_ptr(glm::vec4(0.0f, 0.0f, 0.0f, 0.1f)));
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, glm::value_ptr(glm::vec4(0.0f, 0.0f, 0.0f, 0.1f)));
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, glm::value_ptr(glm::vec4(0.0f, 0.0f, 0.0f, 0.1f)));
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 0.0f);


	glBegin(GL_TRIANGLES);
	for (Vertex* v : vertices) {
		glNormal3fv(glm::value_ptr(v->getNormal()));
		glVertex3fv(glm::value_ptr(v->getPosition()));
	}
	glEnd();

	glEnable(GL_DEPTH_TEST);
	glDisable(GL_BLEND);
	return true;
}

float Shadow::getDeepestPoint()
{
	std::vector<Vertex*> vertices = meshToShadow->getVertices(0);
	float deepestPoint = vertices.at(0)->getPosition().y;
	for (Vertex* v : vertices) {
		if (v->getPosition().y < deepestPoint)
			deepestPoint = v->getPosition().y;
	}
	return deepestPoint;
}
