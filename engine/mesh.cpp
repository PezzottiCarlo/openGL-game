/**
 * @file    mesh.cpp
 * @brief   A simple mesh class
 *
 * @author  Jari Näser (C) SUPSI [jari.naeser@student.supsi.ch]
 * @author  Carlo pezzotti (C) SUPSI [carlo.pezzotti@student.supsi.ch]
 */


 //////////////
 // #INCLUDE //
 //////////////

 // Library main include:
#include "mesh.h"
#include "engine.h"
#include "node.h"
#include "material.h"
#include "texture.h"
#include "vertex.h"

#include <gl/freeglut.h>
#include <iostream>
#include <gtc/type_ptr.hpp>
#include <ext/matrix_transform.hpp>
#include <fstream>
#include <sstream>
#include <vector>
#include <gtx/string_cast.hpp>


 ///////////////////////
// BODY OF CLASS Mesh //
////////////////////////

//constructor
Mesh::Mesh(std::string name, Material* material, Texture* texture) : Node(name) {
	this->material = material;
	this->texture = texture;
    this->lod = 0;
}

//destructor
Mesh::~Mesh() {

}

void Mesh::loadPyramid(float size) {
    std::vector<Vertex*> vertices = genPyram(size);
    for (Vertex* v : vertices) {
        addVertex(v, 0);
    }
}


std::vector<Vertex*> Mesh::genPyram(float size) {
    std::vector<Vertex*> vertices;
    // Define the vertices of a pyramid
    float positions[] = {
		// Front face
		-size, -size,  size,  // Bottom left
		 size, -size,  size,  // Bottom right
		 0.0f,  size,  0.0f,  // Top middle
        // Right face
        size, -size,  size,  // Bottom left
        size, -size, -size,  // Bottom right
        0.0f,  size,  0.0f,  // Top middle
        // Back face
        -size, -size, -size,  // Bottom right
        size, -size, -size,  // Bottom left
        0.0f,  size,  0.0f,  // Top middle
        // Left face
        -size, -size,  size,  // Bottom right
        -size, -size, -size,  // Bottom left
        0.0f,  size,  0.0f,  // Top middle
        // Bottom face left
        -size, -size,  size,  // Top right
        size, -size,  size,  // Top left
        size, -size, -size,  // Bottom left
        // Bottom face right
        -size, -size,  size,  // Top right
        size, -size, -size,  // Bottom left
        -size, -size, -size,  // Bottom right
	};


    float normals[] = {
        // Front face
		0.0f, 0.0f, 1.0f,  // Bottom left
		0.0f, 0.0f, 1.0f,  // Bottom right
		0.0f, 0.0f, 1.0f,  // Top middle
		// Right face
		1.0f, 0.0f, 0.0f,  // Bottom left
		1.0f, 0.0f, 0.0f,  // Bottom right
		1.0f, 0.0f, 0.0f,  // Top middle
		// Back face
		0.0f, 0.0f, -1.0f,  // Bottom right
		0.0f, 0.0f, -1.0f,  // Bottom left
		0.0f, 0.0f, -1.0f,  // Top middle
		// Left face
		-1.0f, 0.0f, 0.0f,  // Bottom right
		-1.0f, 0.0f, 0.0f,  // Bottom left
		-1.0f, 0.0f, 0.0f,  // Top middle
        // Bottom face
        0.0f, -1.0f, 0.0f,  // Top right
        0.0f, -1.0f, 0.0f,  // Top left
        0.0f, -1.0f, 0.0f,  // Bottom left
        // Bottom face
        0.0f, -1.0f, 0.0f,  // Top right
        0.0f, -1.0f, 0.0f,  // Bottom left
        0.0f, -1.0f, 0.0f,  // Bottom right

	};
    int positionsSize = sizeof(positions) / sizeof(positions[0]);
    for (int i = 0; i < (positionsSize)/3; i++) {
        glm::vec3 position(positions[i * 3], positions[i * 3 + 1], positions[i * 3 + 2]);
        glm::vec3 normal(normals[i * 3], normals[i * 3 + 1], normals[i * 3 + 2]);
        Vertex* vertex = new Vertex(position, normal);
        vertices.push_back(vertex);
    }
    return vertices;
}


//load geometry from file
void Mesh::loadGeometryFromFile(const std::string& filePath, float scale) {
    // Open the OBJ file
    std::ifstream objFile(filePath);
    std::vector<glm::vec3> positions;
    if (!objFile.is_open()) {
        //TO-DO manage error
        std::cerr << "Failed to open file: " << filePath << std::endl;
        return;
    }
    // Read the OBJ file line by line
    std::string line;
    while (std::getline(objFile, line)) {
        std::istringstream iss(line);
        std::string token;
        iss >> token;
        if (token == "v") {
            // Read vertex position
            glm::vec3 position;
            iss >> position.x >> position.y >> position.z;
            positions.push_back(position);
        }
        else if (token == "f") {
            // Read face information and create vertices
            std::vector<int> vertexIndices, normalIndices;
            int index;
            while (iss >> index) {
                // Subtract 1 because OBJ indices start from 1, not 0
                vertexIndices.push_back(index - 1);
                // Check for normal indices (you may want to add texture coordinate indices if needed)
                if (iss.peek() == '/') {
                    iss.ignore(); // Skip '/'
                    if (iss.peek() != '/') {
                        iss >> index;
                        normalIndices.push_back(index - 1);
                    }
                    else {
                        // If there's nothing after the second '/', assume only vertex indices
                        normalIndices.push_back(-1);
                    }
                }
            }
            // Create vertices using the collected indices
            for (size_t i = 0; i < vertexIndices.size(); ++i) {
                int vertexIndex = vertexIndices[i];
                int normalIndex = (normalIndices.size() > 0) ? normalIndices[i] : -1;
                if (vertexIndex >= 0 && vertexIndex < positions.size()) {
                    glm::vec3 position = positions[vertexIndex] * scale;
                    glm::vec3 normal;
                    // If normal indices are provided, use them; otherwise, calculate the normal
                    if (normalIndex >= 0 && normalIndex < positions.size()) {
                        normal = positions[normalIndex];
                    }
                    else {
                        // Calculate normal based on the face information
                        glm::vec3 v0 = positions[vertexIndices[0]];
                        glm::vec3 v1 = positions[vertexIndices[1]];
                        glm::vec3 v2 = positions[vertexIndices[2]];
                        normal = -(glm::normalize(glm::cross(v1 - v0, v2 - v0)));
                    }
                    // Debug
                    std::cout << "Vertex: " << glm::to_string(position) << std::endl;
                    std::cout << "Normal: " << glm::to_string(normal) << std::endl;

                    // Assuming addVertex is a method in your Mesh class
                    this->addVertex(new Vertex(position, normal), 0);  // Change the second parameter accordingly (0 is just a placeholder)
                }
            }
        }
    }
    // Close the file
    objFile.close();
}

void Mesh::addVertex(Vertex* v, int lod) {
    if (vertices.size() <= lod) {
        std::vector<Vertex*> tempVec;
        tempVec.push_back(v);
        vertices.push_back(tempVec);
    }
    else
        vertices.at(lod).push_back(v);
}

std::vector<Vertex*> Mesh::getVertices(int lod) {
    return vertices.at(lod);
}

bool LIB_API Mesh::render(glm::mat4 matrix,void* ptr) {
    //TO-DO load texture
    // Set model matrix as current OpenGL matrix:
    glLoadMatrixf(glm::value_ptr(matrix * getFinalMatrix()));
    //Vertex rendering Counter Clock-Wise
    glFrontFace(GL_CCW);
    // Triangles rendering
    glBegin(GL_TRIANGLES);
    for (Vertex* v : vertices.at(lod)) {
        glColor3f(1.0f, 0.0f, 0.0f);
        glNormal3fv(glm::value_ptr(v->getNormal()));
        glTexCoord2fv(glm::value_ptr(v->getTextureCoordinates()));
        glVertex3fv(glm::value_ptr(v->getPosition()));
    }
    glEnd();
    return true;
}