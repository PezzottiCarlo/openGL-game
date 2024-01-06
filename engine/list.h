/**
 * @file	List.h
 * @brief	Definition of the List class.
 *
 * This file contains the declaration of the List class, which represents a list of Node objects.
#include <list>
#include <list>
 * It inherits from the base Object class and is used for managing a collection of nodes in a scene.
 *
 * @author	Jari Näser (C) SUPSI [jari.naeser@student.supsi.ch]
 * @author  [Carlo Pezzotti (C) SUPSI [carlo.pezzotti@student.supsi.ch]
 */

#ifndef LIST
#define LIST

#include <list>
#include "lib.h"
#include "object.h"
#include "node.h"

 /**
  * @brief List class.
  *
  * This class represents a list of Node objects. It inherits from the base Object class
  * and is used for managing a collection of nodes in a scene.
  */
class LIB_API List : public Object {
public:
    /**
     * @brief Default constructor for the List class.
     */
    List() {}

    /**
     * @brief Add a Node to the list.
     * @param node The Node to be added to the list.
     */
    void addEntry(Node* node);

    void popEntry();

    /**
     * @brief Render function for the list of objects.
     *
     * This function renders all the nodes in the list based on the given transformation matrix.
     *
     * @param transform The transformation matrix for rendering the list.
     * @param data Additional data for rendering (optional).
     * @return A boolean indicating the success of the rendering operation.
     */
    bool render(glm::mat4 transform, void* data) override;

    /**
     * @brief Clear the list of objects.
     */
    void clear();

    /**
     * @brief Get a Node from the list based on its index.
     * @param index The index of the Node in the list.
     * @return The Node at the specified index.
     */
    Node* getObject(int index);

    /**
     * @brief Get a Node from the list based on its ID.
     * @param id The ID of the Node to retrieve.
     * @return The Node with the specified ID.
     */
    Node* getObjectById(int id);

    /**
     * @brief Get the size of the list.
     * @return The number of Nodes in the list.
     */
    int size();

private:
    std::list<Node*> objectsList;  ///< The list of Node objects.
};

#endif
