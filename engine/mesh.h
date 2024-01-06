/**
 * @file	mesh.h
 * @brief	Simple mesh class
 *
 * This file contains the declaration of the Mesh class, a simple mesh representation.
 * It inherits from the base Node class and includes features for adding vertices, setting LOD,
 * rendering, and retrieving material information.
 *
 * @author	Jari Näser (C) SUPSI [jari.naeser@student.supsi.ch]
 * @author  Carlo Pezzotti (C) SUPSI [carlo.pezzotti@student.supsi.ch]
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
    /**
     * @brief Constructor for the Mesh class.
     *
     * @param name The name of the mesh.
     * @param material The material associated with the mesh.
     */
    Mesh(std::string name, Material material);

    /**
     * @brief Destructor for the Mesh class.
     */
    ~Mesh();

public:
    /**
     * @brief Add a vertex to the mesh at a specific Level of Detail (LOD).
     *
     * @param v The vertex to add.
     * @param lod The Level of Detail at which to add the vertex.
     */
    void addVertex(Vertex* v, int lod);

    /**
     * @brief Get the vertices of the mesh at a specific Level of Detail (LOD).
     *
     * @param lod The Level of Detail.
     * @return A vector of vertices at the specified LOD.
     */
    std::vector<Vertex*> getVertices(int lod);

    /**
     * @brief Render function for the mesh.
     *
     * This function renders the mesh based on the given transformation matrix.
     *
     * @param transform The transformation matrix for rendering the mesh.
     * @param data Additional data for rendering (optional).
     * @return A boolean indicating the success of the rendering operation.
     */
    virtual bool render(glm::mat4 transform, void* data) override;

    /**
     * @brief Get the material associated with the mesh.
     * @return A pointer to the material.
     */
    Material* getMaterial();

    /**
     * @brief Get the color of the mesh based on a specific ID.
     *
     * @param id The ID to retrieve the color for.
     * @return The color corresponding to the provided ID.
     */
    glm::vec4 getColorBasedOnId(int id);

    /**
     * @brief Test method for the Mesh class.
     * @return An integer indicating the result of the test.
     */
    static int test();

protected:
    /**
     * @brief Level of Detail (LOD) of the mesh.
     */
    int lod = 0;

    ///////////
private: //
    ///////////
        /**
         * @brief Material associated with the mesh.
         */
    Material material;

    /**
     * @brief Vector of vectors containing vertices for different Levels of Detail (LODs).
     */
    std::vector<std::vector<Vertex*>> vertices;
};
