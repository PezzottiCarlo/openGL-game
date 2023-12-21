#include "material.h"

int Material::test() {

	Material material("TestMaterial", glm::vec4(1.0), glm::vec4(1.0), glm::vec4(1.0), glm::vec4(1.0), 1.0);

	// test setEmission
	assert(material.getEmission() == glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
	material.setEmission(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
	assert(material.getEmission() == glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));

	// test setAmbient
	assert(material.getAmbient() == glm::vec4(1.0, 1.0f, 1.0f, 1.0f));
	material.setAmbient(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
	assert(material.getAmbient() == glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));

	// test setDiffuse
	assert(material.getDiffuse() == glm::vec4(.5f, .5f, .5f, 1.0f));
	material.setDiffuse(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
	assert(material.getDiffuse() == glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));

	// test setSpecular
	assert(material.getSpecular() == glm::vec4(.5f, .5f, .5f, 1.0f));
	material.setSpecular(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
	assert(material.getSpecular() == glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));

	// test setShininess
	assert(material.getShininess() == 1.0f);
	material.setShininess(0.2f);
	assert(material.getShininess() == 0.2f);

	return 0;
}