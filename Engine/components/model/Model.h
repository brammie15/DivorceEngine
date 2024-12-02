//
// Created by Bram on 02/12/2024.
//

#ifndef SUPEREPIKGAME_MODEL_H
#define SUPEREPIKGAME_MODEL_H


#include "Mesh.h"
#include "Material.h"

class Model
{
public:
    Model();
    Model(Mesh* mesh, Material* material);
    ~Model() {};

    Mesh* getMesh();
    Material* getMaterial();

    void setMesh(Mesh* mesh);
    void setMaterial(Material* material);

private:
    Mesh* m_mesh;
    Material* m_material;
};


#endif //SUPEREPIKGAME_MODEL_H
