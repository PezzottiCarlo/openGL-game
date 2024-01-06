/**
 * @file    ov_object.h
 * @brief   Stripped-down redefinition of OvObject.
 *
 * This file contains a simplified version of the OvObject class, focusing on the Type enumeration.
 * It defines different types of entities, including O_OBJECT, O_NODE, O_OBJECT2D, O_OBJECT3D, O_LIST, and more.
 *
 * @author	Jari Näser (C) SUPSI [jari.naeser@student.supsi.ch]
 * @author  Carlo Pezzotti (C) SUPSI [carlo.pezzotti@student.supsi.ch]
 */

#pragma once

 /**
  * @brief Stripped-down redefinition of OvObject (just for the chunk IDs).
  */
class OvObject
{
public:
    /**
     * @brief Enumeration representing the type of entities.
     */
    enum class Type : int
    {
        O_OBJECT = 0,       ///< Generic object type.
        O_NODE,             ///< Node type.
        O_OBJECT2D,         ///< 2D object type.
        O_OBJECT3D,         ///< 3D object type.
        O_LIST,             ///< List type.

        // Derived classes:
        O_BUFFER,           ///< Buffer type.
        O_SHADER,           ///< Shader type.
        O_TEXTURE,          ///< Texture type.
        O_FILTER,           ///< Filter type.
        O_MATERIAL,         ///< Material type.
        O_FBO,              ///< Framebuffer object type.
        O_QUAD,             ///< Quad type.
        O_BOX,              ///< Box type.
        O_SKYBOX,           ///< Skybox type.
        O_FONT,             ///< Font type.
        O_CAMERA,           ///< Camera type.
        O_LIGHT,            ///< Light type.
        O_BONE,             ///< Bone type.
        O_MESH,             ///< Mesh type.
        O_SKINNED,          ///< Skinned mesh type.
        O_INSTANCED,        ///< Instanced mesh type.
        O_PIPELINE,         ///< Pipeline type.
        O_EMITTER,          ///< Emitter type.

        // Animation type
        O_ANIM,             ///< Animation type.

        // Physics related:
        O_PHYSICS,          ///< Physics type.

        // Terminator:
        O_LAST              ///< Terminator to indicate the last entity type.
    };
};
