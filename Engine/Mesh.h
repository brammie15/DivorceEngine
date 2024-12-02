//
// Created by Bram on 20/11/2024.
//

#ifndef OPENGLTEMPLATE_MESH_H
#define OPENGLTEMPLATE_MESH_H


#include "DataTypes.h"
#include "Texture.h"
#include "Shader.h"
#include "Transform.h"

#include <vector>
#include <memory>


class Mesh {
public:
    Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, const std::vector<std::shared_ptr<Texture>> &textures,
         const Transform &transform);

// mesh data
    std::vector<Vertex> m_verticies;
    std::vector<unsigned int> m_indices;
    std::vector<std::shared_ptr<Texture>> m_textures;

    void Draw(Shader &shader);

private:
    //  render data
    unsigned int VAO, VBO, EBO;

    Transform m_transform;

    void setupMesh();

};


#endif //OPENGLTEMPLATE_MESH_H
