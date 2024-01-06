/**
 * @file    shadow.h
 * @brief   Shadow class definition
 *
 * This file contains the declaration of the Shadow class, which is a derived class from the Node class.
 * It represents a shadow volume associated with a Mesh, allowing for the rendering of shadows.
 *
 * @author  Jari Näser (C) SUPSI [jari.naeser@student.supsi.ch]
 * @author  Carlo Pezzotti (C) SUPSI [carlo.pezzotti@student.supsi.ch]
 */

#pragma once

 ////////////////
 // #INCLUDE //
 ////////////////
#include <memory>
#include <glm/glm.hpp>
#include <GL/freeglut.h>

#include "lib.h"
#include "object.h"
#include "node.h"
#include "mesh.h"
#include "vertex.h"

/////////////////////
// FORWARD DECLARATION //
/////////////////////
class Node;

/////////////
// CLASSES //
/////////////

/**
 * @brief Shadow class representing a shadow volume associated with a Mesh.
 */
class LIB_API Shadow : public Node {
    //////////
public: //
    /**
     * @brief Constructor for Shadow.
     *
     * @param mesh The Mesh associated with the shadow.
     */
    Shadow(Mesh* mesh);

    /**
     * @brief Destructor for Shadow.
     */
    ~Shadow();

public:
    /**
     * @brief Add a vertex to the shadow volume.
     *
     * @param v The vertex to add.
     */
    void addVertex(Vertex* v);

    /**
     * @brief Get the vector of vertices in the shadow volume.
     *
     * @return The vector of vertices in the shadow volume.
     */
    std::vector<Vertex*> getVertices();

    /**
     * @brief Render function for the shadow volume.
     *
     * @param transform The transformation matrix for rendering the shadow volume.
     * @param data Additional data for rendering (optional).
     * @return A boolean indicating the success of the rendering operation.
     */
    virtual bool render(glm::mat4 transform, void* data) override;

private: //
    ///////////
    /**
     * @brief Get the depth of the deepest point in the shadow volume.
     *
     * @return The depth of the deepest point.
     */
    float getDeepestPoint();

    /**
     * @brief Pointer to the Mesh associated with the shadow volume.
     */
    Mesh* meshToShadow;

    /**
     * @brief Vector of vertices in the shadow volume.
     */
    std::vector<Vertex*> vertices;
};