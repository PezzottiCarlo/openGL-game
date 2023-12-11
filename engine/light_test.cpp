#include "light.h"

int run_light_test() {

	Light light("TestLight");

	// test setIntensity
	assert(light.getIntensity() == 1.0f);
	light.setIntensity(2.0f);
	assert(light.getIntensity() == 2.0f);

	// test setColor
	assert(light.getColor()[0] == 1.0f);
	assert(light.getColor()[1] == 1.0f);
	assert(light.getColor()[2] == 1.0f);
	light.setColor(0.1f, 0.2f, 0.4f);
	assert(light.getColor()[0] == 0.1f);
	assert(light.getColor()[1] == 0.2f);
	assert(light.getColor()[2] == 0.4f);

	// test setLightType
	assert(light.getLightType() == Light::LightType::DIRECTIONAL);
	light.setLightType(Light::LightType::POINT);
	assert(light.getLightType() == Light::LightType::POINT);

	return 0; 
}