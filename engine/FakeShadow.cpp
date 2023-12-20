#include "fakeShadow.h"

LIB_API FakeShadow::FakeShadow(const std::string name, std::shared_ptr<Material> material, Mesh* model) :
	Mesh{name, material }
{
	this->material = material;
	this->mesh = model;
};

std::shared_ptr<Material> LIB_API FakeShadow::getMaterial() {
	return material;
}

Mesh* FakeShadow::getMesh() {
	return mesh;
}

void LIB_API FakeShadow::setMaterial(std::shared_ptr<Material> material) {
	this->material = material;
}

void LIB_API FakeShadow::setMesh(Mesh* mesh) {
	this->mesh = mesh;
}

void LIB_API FakeShadow::setCastShadow(bool value) {
	this->castShadow = value;
}

bool LIB_API FakeShadow::render(glm::mat4 matrix, void* ptr) {
	return true;
}


