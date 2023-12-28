#include <GL/freeglut.h>
#include <glm/gtc/type_ptr.hpp>
#include <math.h>

#include "material.h"
#include "node.h"


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


/*glm::vec4 getAmbientFromAlbedo(glm::vec4 albedo) {
	return albedo * 0.2f;
}

glm::vec4 getSpecularFromAlbedo(glm::vec4 albedo) {
	return albedo * 0.4f;
}

glm::vec4 getDiffuseFromAlbedo(glm::vec4 albedo) {
	return albedo * 0.6f;
}

float getShininessFromRoughness(float roughness) {
	return (1 - sqrt(roughness)) * 128.0f;
}*/

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