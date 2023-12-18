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
Mesh::Mesh(std::string name, std::shared_ptr<Material> material) : Node(name) {
    this->material = material;
}

//destructor
Mesh::~Mesh() {

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
    
    //if (material->getTexture() != nullptr) material->getTexture()->render(matrix, ptr);
    if (material != nullptr) material->render(matrix, ptr);
    
    glLoadMatrixf(glm::value_ptr(matrix * getFinalMatrix()));
    std::cout << "Vertex for [ " << this->getName() << "]" << std::endl;

    //Vertex rendering Counter Clock-Wise
    glFrontFace(GL_CCW);
    glBegin(GL_TRIANGLES);

    for (Vertex* v : vertices.at(lod)) {
        //std::cout << "\t" << glm::to_string(v->getPosition()) << std::endl;
        glColor3f(1.0f, 0.0f, 0.0f);
        glNormal3fv(glm::value_ptr(v->getNormal()));
        glTexCoord2fv(glm::value_ptr(v->getTextureCoordinates()));
        glVertex3fv(glm::value_ptr(v->getPosition()));
    }

    glEnd();
    return true;
}

std::shared_ptr<Material> Mesh::getMaterial() {
	return material;
}