#include "pointLight.h"
#include <GL/freeglut.h>

LIB_API PointLight::PointLight(const std::string name, const int lightNumber, const glm::vec4 ambient,
	const glm::vec4 diffuse, const glm::vec4 specular, const float cutOff) :
	Light{ name, lightNumber, ambient, diffuse, specular }, cutOff(cutOff) {};

bool LIB_API PointLight::render(glm::mat4 matrix, void* ptr) {
	glLightfv(getLightNumber(), GL_SPOT_CUTOFF, &cutOff);

	Light::render(matrix, ptr);

	return true;
}