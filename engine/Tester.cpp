#include <iostream>
#include "light.h"
#include "material.h"
#include "mesh.h"

int main() {

	int status = 0;

	// Run all tests
	status |= Light::test();
	status |= Material::test();
	status |= Mesh::test();
	status |= Node::test();
	status |= Texture::test();

	if (!status) {
		std::cout << "[OK] All tests passed successfully!" << std::endl;
	}else {
		std::cout << "[ERROR] Some tests have failed." << std::endl;
	}

	return 0;
}