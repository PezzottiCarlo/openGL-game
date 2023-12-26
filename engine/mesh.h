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
class LIB_API Mesh : public Node {
//////////
public: //
//////////
    // Constructor with a name, material, and texture
    Mesh(std::string name, std::shared_ptr<Material> material);

    // Destructor
    ~Mesh();
public:
    // Add a vertex to the mesh
    void addVertex(Vertex* v, int lod);
    // Get vertices
    std::vector<Vertex*> getVertices(int lod);
    // Set LOD
    virtual bool render(glm::mat4, void*) override;
    // Get material
    std::shared_ptr<Material> getMaterial();

    // Test method
    static int test();


protected:
    // LOD
    int lod = 0;

///////////
private: //
///////////
    // Mesh-specific members
    std::shared_ptr<Material> material;
    std::vector<std::vector<Vertex*>> vertices;
};
