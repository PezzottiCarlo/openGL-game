#include "material.h"
#include "node.h"
#include <gl/freeglut.h>
#include <gtc/type_ptr.hpp>

// Constructor
Material::Material(const std::string name) {
    Object::setName(name);
	diffuseTexturePath = "";
	shininess = 0.0f;
	this->setAmbient(glm::vec4(1.0, 1.0f, 1.0f, 1.0f));
	this->setEmission(glm::vec4(0, 0, 0, 1.0f));
	this->setDiffuse(glm::vec4(.5f, .5f, .5f, 1.0f));
	this->setSpecular(glm::vec4(.5f, .5f, .5f, 1.0f));
	this->setShininess(1.0f);
}

// Destructor
Material::~Material() {
    // Cleanup, if needed
}


glm::vec4 LIB_API Material::getEmission() {
	return emission;
}
glm::vec4 LIB_API Material::getAmbient() {
	return ambient;
}
glm::vec4 LIB_API Material::getDiffuse() {
	return diffuse;
}
glm::vec4 LIB_API Material::getSpecular() {
	return specular;
}
float LIB_API Material::getShininess() {
	return shininess;
}

void LIB_API Material::setEmission(glm::vec4 emission) {
	this->emission = emission;
}
void LIB_API Material::setAmbient(glm::vec4 ambient) {
	this->ambient = ambient;
}
void LIB_API Material::setDiffuse(glm::vec4 diffuse) {
	this->diffuse = diffuse;
}
void LIB_API Material::setSpecular(glm::vec4 specular) {
	this->specular = specular;
}
void LIB_API Material::setShininess(float shininess) {
	this->shininess = shininess;
}

// Render the material
bool LIB_API Material::render(glm::mat4, void*) {
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shininess);
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, glm::value_ptr(emission));
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, glm::value_ptr(ambient));
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, glm::value_ptr(diffuse));
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, glm::value_ptr(specular));
    return true;
}