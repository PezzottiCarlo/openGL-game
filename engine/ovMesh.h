/**
 * @file    ov_mesh.h
 * @brief   Stripped-down redefinition of OvMesh.
 *
 * This file contains a simplified version of the OvMesh class, focusing on the Subtype enumeration.
 * It defines different subtypes of meshes, including DEFAULT, NORMALMAPPED, and TESSELLATED.
 *
 * @author	Jari Näser (C) SUPSI [jari.naeser@student.supsi.ch]
 * @author  Carlo Pezzotti (C) SUPSI [carlo.pezzotti@student.supsi.ch]
 */

#pragma once

 /**
  * @brief Stripped-down redefinition of OvMesh (just for the subtypes).
  */
class OvMesh
{
public:
    /**
     * @brief Enumeration representing the kind of mesh.
     */
    enum class Subtype : int
    {
        DEFAULT = 0,        ///< Default mesh type.
        NORMALMAPPED,       ///< Normal-mapped mesh type.
        TESSELLATED,        ///< Tessellated mesh type.
        LAST                ///< Terminator to indicate the last subtype.
    };
};
