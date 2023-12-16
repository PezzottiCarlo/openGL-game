#include "fakeShadow.h"

FakeShadow::FakeShadow(const std::string name, std::shared_ptr<Material> material, Mesh* mesh) {
	Object::setId(Object::getNextId());
	Object::setName(name);
	this->setMaterial(material);
	this->setMesh(mesh);
}

std::shared_ptr<Material> LIB_API FakeShadow::getMaterial() {
	return material;
}

Mesh* LIB_API FakeShadow::getMesh() {
	return mesh;
}

void LIB_API FakeShadow::setMaterial(std::shared_ptr<Material> material) {
	this->material = material;
}

void LIB_API FakeShadow::setMesh(Mesh* mesh) {
	this->mesh = mesh;
}

