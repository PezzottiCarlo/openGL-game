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

#include "node.h"
#include "vertex.h"
#include "material.h"
#include "texture.h"



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
    Shadow(std::string name);

    // Destructor
    ~Shadow();
public:
    void addVertex(Vertex* v);
    std::vector<Vertex*> getVertices();
    virtual bool render(glm::mat4, void*) override;

private: //
    ///////////
    float getDeepestPoint();
    std::vector<Vertex*> vertices;
};
