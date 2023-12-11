#include "mesh.h"

int run_mesh_test() {

	Material material("TestMaterial");
	Texture texture("TestTexture");
	Vertex vertex(glm::vec3(1.0), glm::vec3(1.0));

	Mesh mesh("TestMesh", &material, &texture);

	// test get and add vertices
	std::vector<Vertex*> initialVertices = mesh.getVertices(0);
	mesh.addVertex(&vertex, 0);
	std::vector<Vertex*> finalVertices = mesh.getVertices(0);

	// TBD
	assert(initialVertices.size() < finalVertices.size());

	return 0;
}