/**
 * @file	fakeShadow.h
 * @brief	Fake shadow class definition
 *
 * @author	Jari Näser (C) SUPSI [jari.naeser@student.supsi.ch]
 * @author  Carlo pezzotti (C) SUPSI [carlo.pezzotti@student.supsi.ch]
 */

#pragma once

 /////////////
 // #INCLUDE //
 /////////////

#include <string>   
#include "object.h"  
#include "texture.h"
#include <memory>
#include "material.h"
#include "mesh.h"

/////////////
// CLASSES //
/////////////

/**
 * @brief Material class
 */
class LIB_API FakeShadow : public Mesh {
//////////
public: //
//////////
// 
    // Constructor
    FakeShadow(const std::string name, std::shared_ptr<Material> material, Mesh* mesh);

    // Getters
    std::shared_ptr<Material> getMaterial();
    Mesh* getMesh();

    // Setters
    void setMaterial(std::shared_ptr<Material> material);
    void setMesh(Mesh* mesh);

    virtual bool render(glm::mat4, void*) override;

    void setCastShadow(bool);

///////////
private: //
///////////
    // Material settings
    std::shared_ptr<Material> material;
    Mesh* mesh;
    bool castShadow = true;
};