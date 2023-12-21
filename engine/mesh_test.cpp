#include "mesh.h"

int Mesh::test() {

	Material material("TestMaterial", glm::vec4(1.0), glm::vec4(1.0), glm::vec4(1.0), glm::vec4(1.0), 1.0);
	Texture texture("TestTexture");
	material.setTexture(&texture);

	Vertex vertex(glm::vec3(1.0), glm::vec3(1.0));

	Mesh mesh("TestMesh", std::make_shared<Material>(material));
	
	// test get and add vertices

	/*std::vector<Vertex*> initialVertices = mesh.getVertices(0);
	mesh.addVertex(&vertex, 0);
	std::vector<Vertex*> finalVertices = mesh.getVertices(0);

	// TBD
	assert(initialVertices.size() < finalVertices.size());*/

	return 0;
}