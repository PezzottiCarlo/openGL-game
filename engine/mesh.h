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

#include "engine.h"
#include "node.h"
#include "vertex.h"
#include "material.h"
#include "texture.h"

#include <glm.hpp>

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
    Mesh(std::string name, Material* material, Texture* texture);

    // Destructor
    ~Mesh();
public:
    // Load geometry from a file
    void loadGeometryFromFile(const std::string& filePath, float scale);
    // Accessors for material and texture
    Material* getMaterial() const;
    Texture* getTexture() const;
    // Add a vertex to the mesh
    void addVertex(Vertex* v, int lod);
    // Get vertices
    std::vector<Vertex*> getVertices(int lod);
    // Set LOD
    virtual bool render(glm::mat4, void*) override;
    // Get material
    Material* getMaterial();
    //Get texture
    Texture* getTexture();


    //TESTING METHOD - REMOVE
    void loadPyramid(float size);
    std::vector<Vertex*> genPyram(float size);

    // Test method
    static int test();


protected:
    // LOD
    int lod = 0;

///////////
private: //
///////////
    // Mesh-specific members
    Material* material;
    Texture* texture;
    std::vector<std::vector<Vertex*>> vertices;
};
