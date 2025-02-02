/**
 * @file    mesh.cpp
 * @brief   A simple mesh class
 *
 * @author  Jari N�ser (C) SUPSI [jari.naeser@student.supsi.ch]
 * @author  Carlo pezzotti (C) SUPSI [carlo.pezzotti@student.supsi.ch]
 */

 //////////////
 // #INCLUDE //
 //////////////

 // Library main include:
#include <GL/freeglut.h>
#include <iostream>
#include <glm/gtc/type_ptr.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <fstream>
#include <sstream>
#include <vector>
#include <glm/gtx/string_cast.hpp>

#include "mesh.h"
#include "node.h"
#include "material.h"
#include "texture.h"
#include "vertex.h"

 ///////////////////////
// BODY OF CLASS Mesh //
////////////////////////

//constructor
Mesh::Mesh(std::string name, Material material) : Node(name) {
    this->material = material;
    this->vertices;
}

//destructor
Mesh::~Mesh() {}

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

    material.render(matrix, ptr);
    glLoadMatrixf(glm::value_ptr(matrix * getFinalMatrix()));
    glFrontFace(GL_CCW);
    glBegin(GL_TRIANGLES);
    //render with the scale
    for (Vertex* v : vertices.at(lod)) {
        glColor4fv(glm::value_ptr(getColorBasedOnId(getId())));
        glNormal3fv(glm::value_ptr(v->getNormal()*getScale()));
        glTexCoord2fv(glm::value_ptr(v->getTextureCoordinates()*getScale()));
        glVertex3fv(glm::value_ptr(v->getPosition()*getScale()));
    }
    glEnd();
    return true;
}

Material* Mesh::getMaterial() {
	return &material;
}

glm::vec4 Mesh::getColorBasedOnId(int id)
{
    float r = (float)((id >> 16) & 0xFF) / 255.0f;
    float g = (float)((id >> 8) & 0xFF) / 255.0f;
    float b = (float)((id >> 0) & 0xFF) / 255.0f;
    glm::vec4 color = glm::vec4(r, g, b, 1.0f);
    return color;
}
