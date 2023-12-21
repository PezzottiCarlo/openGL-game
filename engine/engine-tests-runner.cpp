#include <iostream>
#include "light.h"
#include "material.h"
#include "mesh.h"
#include "engine-tests-runner.h"


// The main method gets invoked on the gitlab's docker image through the makefile
int main() {
	int status = 0;

	// Run all tests
	status |= Light::test();
	status |= Material::test();
	status |= Mesh::test();
	status |= Node::test();
	status |= Texture::test();

	return status;
}

// This method is used to verify the tests before every single execution of the client
// For development purposes only
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