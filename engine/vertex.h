#pragma once

#include "lib.h"
#include "engine.h"
#include <glm.hpp>

class LIB_API Vertex {

	public:
		Vertex(glm::vec3 position, glm::vec3 normal);
		~Vertex();

	public:
		glm::vec3 getPosition();
		glm::vec3 getNormal();
		glm::vec2 getTextureCoordinates();
		void setTextureCoordinates(glm::vec2 textCoord);

	private:
		glm::vec3 position;
		glm::vec3 normal;
		glm::vec2 textureCoordinates;

};