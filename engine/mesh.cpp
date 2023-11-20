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
#include "GL/freeglut.h"

 ///////////////////////
// BODY OF CLASS Mesh //
////////////////////////

//constructor
Mesh::Mesh(std::string name, Material* material, Texture* texture) : Node(name) {
	this->material = material;
	this->texture = texture;
}

//destructor
Mesh::~Mesh() {

}

//load geometry from file
void Mesh::loadGeometryFromFile(const std::string& filePath) {
	//load geometry from file
}

//render the mesh
void Mesh::render() {
	//render a simple cube
    float size = 10 / 2.0f;

    // Back:
    glBegin(GL_TRIANGLE_STRIP);
    glNormal3f(0.0f, 0.0f, -1.0f);
    glVertex3f(size, -size, -size);
    glVertex3f(-size, -size, -size);
    glVertex3f(size, size, -size);
    glVertex3f(-size, size, -size);
    glEnd();

    // Front:	      
    glBegin(GL_TRIANGLE_STRIP);
    glNormal3f(0.0f, 0.0f, 1.0f);
    glVertex3f(-size, -size, size);
    glVertex3f(size, -size, size);
    glVertex3f(-size, size, size);
    glVertex3f(size, size, size);
    glEnd();

    // Left:	      
    glBegin(GL_TRIANGLE_STRIP);
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glVertex3f(-size, size, -size);
    glVertex3f(-size, -size, -size);
    glVertex3f(-size, size, size);
    glVertex3f(-size, -size, size);
    glEnd();

    // Right:	      
    glBegin(GL_TRIANGLE_STRIP);
    glNormal3f(1.0f, 0.0f, 0.0f);
    glVertex3f(size, -size, -size);
    glVertex3f(size, size, -size);
    glVertex3f(size, -size, size);
    glVertex3f(size, size, size);
    glEnd();

    // Bottom:	      
    glBegin(GL_TRIANGLE_STRIP);
    glNormal3f(0.0f, -1.0f, 0.0f);
    glVertex3f(-size, -size, -size);
    glVertex3f(size, -size, -size);
    glVertex3f(-size, -size, size);
    glVertex3f(size, -size, size);
    glEnd();

    // Top:	      
    glBegin(GL_TRIANGLE_STRIP);
    glNormal3f(0.0f, 1.0f, 0.0f);
    glVertex3f(size, size, -size);
    glVertex3f(-size, size, -size);
    glVertex3f(size, size, size);
    glVertex3f(-size, size, size);
    glEnd();
}