/**
 * @file	mesh.h
 * @brief	Simple mesh class
 *
 * @author	Jari Näser (C) SUPSI [jari.naeser@student.supsi.ch]
 * @author  Carlo pezzotti (C) SUPSI [carlo.pezzotti@student.supsi.ch]
 */

#pragma once

 ////////////////
 // #INCLUDE //
 ////////////////
#include <memory>
#include <glm/glm.hpp>
#include <gl/freeglut.h>

#include "object.h"
#include "node.h"
#include "mesh.h"
#include "vertex.h"




/////////////
// FORWARD DECLARATION //
/////////////

class Node;

/////////////
// CLASSES //
/////////////

/**
 * @brief Simple mesh class.
 */
class LIB_API Shadow : public Node {
    //////////
public: //
    Shadow(Mesh* mesh);

    // Destructor
    ~Shadow();
public:
    void addVertex(Vertex* v);
    std::vector<Vertex*> getVertices();
    virtual bool render(glm::mat4, void*) override;

private: //
    ///////////
    float getDeepestPoint();
    Mesh* meshToShadow;
    std::vector<Vertex*> vertices;
};
