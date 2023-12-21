#include "pointLight.h"

#ifndef SPOT_LIGHT
#define SPOT_LIGHT

class LIB_API SpotLight : public PointLight {

public:
	SpotLight(const std::string name, const int lightNumber, const glm::vec4 ambient,
		const glm::vec4 diffuse, const glm::vec4 specular, const float cutOff, const glm::vec3 direction);
	~SpotLight() {};

public:
	bool render(glm::mat4 cameraInv, void* ptr) override;

private:
	glm::vec3 direction;
};

#endif 