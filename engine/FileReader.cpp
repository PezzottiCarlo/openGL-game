#include "FileReader.h"
#include "OvObject.h"
#include "OvMesh.h"
#include "OvLight.h"
#include "Mesh.h"
#include "Light.h"
#include <string>
#include <GL/freeglut.h>
#include <gtc/packing.hpp>
#include <iostream>

#pragma warning(disable : 4996)

FileReader::FileReader() {}

FileReader::~FileReader() {
	materials.clear();
	tempVertices.clear();
}

Node* FileReader::readFile(const char* path) {

	// Open file:
	FILE* dat = fopen(path, "rb");
	if (dat == nullptr)
	{
		std::cout << "ERROR: unable to open file '" << path << "'" << std::endl;
		return nullptr;
	}

	Material* shadow_material = new Material("shadow_material");
	shadow_material->setAmbient(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
	shadow_material->setDiffuse(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
	shadow_material->setSpecular(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
	shadow_material->setShininess(0.0f);
	shadow_material->setEmission(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
	materials.insert(std::pair<std::string, Material*>(shadow_material->getName(), shadow_material));

	Node* root = recursiveLoad(dat);
	fclose(dat);

	return root;
}

// Recursive loading function
Node* FileReader::recursiveLoad(FILE* dat)
{
	return nullptr;
}
