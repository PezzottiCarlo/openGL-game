#include "light.h"

#ifndef POINT_LIGHT
#define POINT_LIGHT

class LIB_API PointLight : public Light {

public:
	PointLight(const std::string name, const int lightNumber, const glm::vec4 ambient, const glm::vec4 diffuse, const glm::vec4 specular, const float cutOff = 180.0f);
	~PointLight() {};

public:
	virtual bool render(glm::mat4,void*) override;

private:
	float cutOff;
};

#endif 