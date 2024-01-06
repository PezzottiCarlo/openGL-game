#include "mesh.h"

int Mesh::test() {

	Material material("TestMaterial", glm::vec4(1.0), glm::vec4(1.0), glm::vec4(1.0), glm::vec4(1.0), 1.0);
	Texture texture("TestTexture");
	material.setTexture(&texture);

	Vertex vertex(glm::vec3(1.0), glm::vec3(1.0));

	Mesh mesh("TestMesh", material);

	return 0;
}