#include "light.h"
#include "node.h"
// Constructor  
Light::Light(const std::string& name) : Node(name) {
	setIntensity(1.0f);
	setColor(1.0f, 1.0f, 1.0f);
}

// Destructor
Light::~Light() {
}

// Set light intensity
void Light::setIntensity(float intensity) {
    this->intensity = intensity;
}

// Set light color
void Light::setColor(float r, float g, float b) {
    color[0] = r;
    color[1] = g;
    color[2] = b;
}

// Render the light
void Light::render() {

}