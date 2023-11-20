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
    Mesh(std::string name, Material* material, Texture* texture);

    // Destructor
    ~Mesh();

    // Load geometry from a file
    void loadGeometryFromFile(const std::string& filePath);

    // Render the mesh
    void render();

    // Accessors for material and texture
    Material* getMaterial() const;
    Texture* getTexture() const;

///////////
private: //
///////////
    // Mesh-specific members
    Material* material;
    Texture* texture;
};
