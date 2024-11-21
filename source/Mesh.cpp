//
// Created by Bram on 20/11/2024.
//

#include "Mesh.h"

#include <utility>
#include <glad/glad.h>




Mesh::Mesh(const std::vector<Vertex> &vertices, const std::vector<unsigned int> &indices,
           const std::vector<Texture> &textures) : vertices(vertices), indices(indices), textures(textures) {
    setupMesh();
}

void Mesh::setupMesh()
{
    // create buffers/arrays
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);
    // load data into vertex buffers
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

    // set the vertex attribute pointers
    // vertex Positions
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
    // vertex normals
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));
    // vertex texture coords
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texCoords));

    glBindVertexArray(0);
}

void Mesh::Draw(Shader &shader) {
    // bind appropriate textures
    uint8_t diffuseNr  = 1;
    uint8_t specularNr = 1;
    uint8_t normalNr   = 1;
    uint8_t heightNr   = 1;
//    for(unsigned int i = 0; i < textures.size(); i++)
//    {
//        glActiveTexture(GL_TEXTURE0 + i); // active proper texture unit before binding
//        // retrieve texture number (the N in diffuse_textureN)
//        std::string number;
//        std::string name = textures[i].type;
//        if(name == "diffuse")
//            number = std::to_string(diffuseNr++);
//        else if(name == "texture_specular")
//            number = std::to_string(specularNr++); // transfer unsigned int to string
//        else if(name == "texture_normal")
//            number = std::to_string(normalNr++); // transfer unsigned int to string
//        else if(name == "texture_height")
//            number = std::to_string(heightNr++); // transfer unsigned int to string
//
//        // now set the sampler to the correct texture unit
//        std::cout << "Setting uniform: " << (name + number) << std::endl;
//        glUniform1i(glGetUniformLocation(shader.ID, (name + number).c_str()), i);
//        // and finally bind the texture
//        textures[i].BindTexture();
//    }

    //Time for a temp hack
//    glActiveTexture(GL_TEXTURE0);
//    textures[0].BindTexture();

    // draw mesh
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, static_cast<unsigned int>(indices.size()), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);

    // always good practice to set everything back to defaults once configured.
    glActiveTexture(GL_TEXTURE0);
}


