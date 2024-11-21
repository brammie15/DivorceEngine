//
// Created by Bram on 20/11/2024.
//

#ifndef OPENGLTEMPLATE_MESH_H
#define OPENGLTEMPLATE_MESH_H


#include "DataTypes.h"
#include "Texture.h"
#include "Shader.h"

#include <vector>

class Mesh {
public:
    // mesh data
    std::vector<Vertex>       vertices;
    std::vector<unsigned int> indices;
    std::vector<Texture >      textures;

    Mesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices, const std::vector<Texture>& textures);
    void Draw(Shader &shader);
private:
    //  render data
    unsigned int VAO, VBO, EBO;

    void setupMesh();
};


#endif //OPENGLTEMPLATE_MESH_H
