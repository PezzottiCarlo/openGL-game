/**
 * @file    ovoreader.h
 * @brief   OvoReader class for reading OVO files.
 *
 * This file contains the declaration of the OvoReader class, which is responsible for reading OVO files.
 * It includes functions for reading OVO files, loading materials, vertices, and creating a hierarchical scene structure.
 *
 * @author	Jari Näser (C) SUPSI [jari.naeser@student.supsi.ch]
 * @author  Carlo Pezzotti (C) SUPSI [carlo.pezzotti@student.supsi.ch]
 */

#pragma once

#include <string>
#include <map>
#include "lib.h"
#include "node.h"
#include "material.h"
#include "vertex.h"

 /**
  * @brief OvoReader class for reading OVO files.
  */
class LIB_API OvoReader {
public:
    /**
     * @brief Constructor for OvoReader.
     */
    OvoReader();

    /**
     * @brief Destructor for OvoReader.
     */
    ~OvoReader();

public:
    /**
     * @brief Read an OVO file and create a hierarchical scene structure.
     *
     * @param path The path to the OVO file.
     * @return A pointer to the root node of the loaded scene.
     */
    Node* readFile(const char* path);

private:
    /**
     * @brief Recursively load data from the OVO file.
     *
     * @param dat The file stream for reading OVO data.
     * @return A pointer to the loaded node.
     */
    Node* recursiveLoad(FILE* dat);

private:
    /**
     * @brief Map to store loaded materials.
     */
    std::map<std::string, Material*> materials;

    /**
     * @brief Vector to store temporary vertices.
     */
    std::vector<Vertex*> tempVertices;
};
