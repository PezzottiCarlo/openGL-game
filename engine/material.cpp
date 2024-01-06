#include <GL/freeglut.h>
#include <glm/gtc/type_ptr.hpp>
#include <math.h>

#include "material.h"
#include "node.h"


Material::Material()
{
	Object::setId(Object::getNextId());
	Object::setName("default");
	this->setEmission(glm::vec4(0.0));
	this->setAmbient(glm::vec4(0.0));
	this->setDiffuse(glm::vec4(0.0));
	this->setSpecular(glm::vec4(0.0));
	this->setShininess(0.0);
}

Material::Material(const std::string name, glm::vec4 _emission, glm::vec4 _ambient, glm::vec4 _diffuse, glm::vec4 _specular, float _shininess) {
	Object::setId(Object::getNextId());
	Object::setName(name);
	this->setEmission(_emission);
	this->setAmbient(_ambient);
	this->setDiffuse(_diffuse);
	this->setSpecular(_specular);
	this->setShininess(_shininess);
}

// Destructor
Material::~Material() {}


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
Texture* Material::getTexture() {
	return texture;
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
void LIB_API Material::setTexture(Texture* texture) {
	this->texture = texture;
}

// Render the material
bool LIB_API Material::render(glm::mat4 matrix, void* ptr) {

	if (texture != nullptr) 
		texture->render(matrix, ptr);

	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shininess);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, glm::value_ptr(ambient));
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, glm::value_ptr(emission));
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, glm::value_ptr(diffuse));
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, glm::value_ptr(specular));
    return true;
}