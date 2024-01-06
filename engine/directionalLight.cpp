#include <iostream>
#include "directionalLight.h"


LIB_API DirectionalLight::DirectionalLight(const std::string name, const int lightNumber, const glm::vec4 ambient, const glm::vec4 diffuse, const glm::vec4 specular) :
	Light{ name, lightNumber, ambient, diffuse, specular } {

}

bool LIB_API DirectionalLight::render(glm::mat4 matrix, void* ptr) {
	Light::render(matrix, ptr);
	return true;
}

void LIB_API DirectionalLight::setTransform(glm::mat4 transform) {
	Light::setTransform(transform);
}