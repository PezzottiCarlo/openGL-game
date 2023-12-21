#include <iostream>
#include "light.h"
#include "material.h"
#include "mesh.h"
#include "tester.h"

void runTests() {

	std::cout << std::endl << "Starting tests..." << std::endl << std::endl;

	int status = 0;

	// Run all tests
	status |= Light::test();
	std::cout << "Light test done" << std::endl;
	status |= Material::test();
	std::cout << "Material test done" << std::endl;
	status |= Mesh::test();
	std::cout << "Mesh test done" << std::endl;
	status |= Node::test();
	std::cout << "Node test done" << std::endl;
	status |= Texture::test();
	std::cout << "Texture test done" << std::endl;

	std::cout << std::endl << "Stopping tests..." << std::endl << std::endl;

	if (!status) {
		std::cout << "[OK] All tests passed successfully!" << std::endl;
	}else {
		std::cout << "[ERROR] Some tests have failed." << std::endl;
	}
}