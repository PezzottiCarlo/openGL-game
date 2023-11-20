#include "material.h"


// Constructor
Material::Material(const std::string name) {
    Object::setName(name);

	// Initialize material settings
	diffuseTexturePath = "";
	shininess = 0.0f;
}

// Destructor
Material::~Material() {
    // Cleanup, if needed
}

// Set material settings
void Material::setMaterialSettings(const std::string& diffuseTexturePath, float shininess) {
    this->diffuseTexturePath = diffuseTexturePath;
    this->shininess = shininess;
}

// Render the material
void Material::render() {

}