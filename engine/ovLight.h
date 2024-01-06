/**
 * @file    ov_light.h
 * @brief   Stripped-down redefinition of OvLight.
 *
 * This file contains a simplified version of the OvLight class, focusing on the Subtype enumeration.
 * It defines different subtypes of lights, including OMNI, DIRECTIONAL, and SPOT.
 *
 * @author	Jari Näser (C) SUPSI [jari.naeser@student.supsi.ch]
 * @author  Carlo Pezzotti (C) SUPSI [carlo.pezzotti@student.supsi.ch]
 */

#pragma once

 /**
  * @brief Stripped-down redefinition of OvLight (just for the subtypes).
  */
class OvLight
{
public:
    /**
     * @brief Enumeration representing the kind of light.
     */
    enum class Subtype : int
    {
        OMNI = 0,           ///< Omni light type.
        DIRECTIONAL,        ///< Directional light type.
        SPOT,               ///< Spot light type.
        LAST                ///< Terminator to indicate the last subtype.
    };
};
