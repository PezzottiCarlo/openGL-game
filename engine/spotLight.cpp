#include <GL/freeglut.h>
#include <glm/gtc/type_ptr.hpp>

#include "spotLight.h"


LIB_API SpotLight::SpotLight(const std::string name, const int lightNumber, const glm::vec4 ambient,
	const glm::vec4 diffuse, const glm::vec4 specular, const float cutOff, const glm::vec3 direction) :
	PointLight{ name, lightNumber, ambient, diffuse, specular, cutOff }, direction(direction) {};

bool LIB_API SpotLight::render(glm::mat4 matrix, void* ptr) {
	glLightfv(getLightNumber(), GL_SPOT_DIRECTION, glm::value_ptr(glm::vec4(direction, 1.0f)));
	PointLight::render(matrix, NULL);

	return true;
}