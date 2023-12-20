#include "PointLight.h"
#include <GL/freeglut.h>

LIB_API PointLight::PointLight(const std::string name, const int lightNumber, const glm::vec4 ambient,
	const glm::vec4 diffuse, const glm::vec4 specular, const float cutOff) :
	Light{ name, lightNumber, ambient, diffuse, specular }, cutOff(cutOff) {};

bool LIB_API PointLight::render(glm::mat4 cameraInv, void* ptr) {
	glLightfv(getLightNumber(), GL_SPOT_CUTOFF, &cutOff);

	Light::render(cameraInv, NULL);

	return true;
}