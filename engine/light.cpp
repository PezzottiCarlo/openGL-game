#include "light.h"
#include "node.h"
#include <gl/freeglut.h>
#include <iostream>
#include <gtc/type_ptr.hpp>

// Constructor  
Light::Light(const std::string& name) : Node(name) {
	setIntensity(1.0f);
	setColor(1.0f, 1.0f, 1.0f);
}

// Destructor
Light::~Light() {
}

float Light::getIntensity() {
    return intensity;
}

// Set light intensity
void LIB_API Light::setIntensity(float intensity) {
    this->intensity = intensity;
}

float* Light::getColor() {
    return color;
}

// Set light color
void LIB_API Light::setColor(float r, float g, float b) {
    color[0] = r;
    color[1] = g;
    color[2] = b;
}

Light::LightType Light::getLightType() {
    return type;
}

void LIB_API Light::setLightType(Light::LightType type) {
	this->type = type;
    switch (type) {
    case DIRECTIONAL:
        lightNumber = GL_LIGHT0;
        break;
    case POINT:
        lightNumber = GL_LIGHT1;
        break;
    case SPOT:
        lightNumber = GL_LIGHT2;
        break;
    default:
        break;
    }
    
    glEnable(GL_LIGHTING);
    glEnable(lightNumber);
    glLightModelf(GL_LIGHT_MODEL_LOCAL_VIEWER, 1.0f);
}

void Light::setPosition() {
    glm::mat4 finalMatrix = getFinalMatrix();
    glm::vec4 finalPosition = finalMatrix[3];
    position = finalPosition;
}

glm::vec4 LIB_API Light::getPosition() {
    return position;
}

void Light::setPosition(glm::vec4 pos) {
    position = pos;
}

// Render the light
bool LIB_API Light::render(glm::mat4 matrix, void* ptr) {
    glLoadMatrixf(glm::value_ptr(matrix * getFinalMatrix()));

    glm::vec4 lightPosition = glm::vec4(0.0f, 0.0f, 0.0f, position.w);

    ///DEBUG
    // Set up the modelview matrix
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
    glMultMatrixf(glm::value_ptr(matrix * getFinalMatrix()));
    // Draw a point at the light position
    glPointSize(5.0f); // Adjust the point size as needed
    glBegin(GL_POINTS);
    glColor3f(1.0f, 1.0f, 1.0f); // White color for the point
    glVertex3f(lightPosition.x, lightPosition.y, lightPosition.z);
    glEnd();
    //END DEBUG

    // Restore the previous modelview matrix
    glPopMatrix();
    GLfloat lightDiffuse[] = { color[0]*intensity, color[1] * intensity, color[2] * intensity, 1.0f };
    glLightfv(lightNumber, GL_DIFFUSE, lightDiffuse);
    GLfloat lightAmbient[] = { color[0] * 0.2f * intensity, color[1] * 0.2f * intensity, color[2] * 0.2f * intensity, 1.0f };
    glLightfv(lightNumber, GL_AMBIENT, lightAmbient);
    GLfloat lightSpecular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    glLightfv(lightNumber, GL_SPECULAR, lightSpecular);
    glLightf(lightNumber, GL_CONSTANT_ATTENUATION, 1.0f);
    glLightf(lightNumber, GL_LINEAR_ATTENUATION, 0.0f);
    glLightf(lightNumber, GL_QUADRATIC_ATTENUATION, 0.0f);
    glLightfv(lightNumber, GL_POSITION, glm::value_ptr(glm::vec4(0.0f, 0.0f, 0.0f, position.w)));

    return true;
}