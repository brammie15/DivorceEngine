#ifndef SUPEREPIKGAME_MESH_H
#define SUPEREPIKGAME_MESH_H



#include <glad/glad.h>
#include <glm/glm.hpp>




#include <iostream>
#include <vector>
#include <string>
#include "Vertex.h"

#include "utils/ModelUtils.h"

#include "tiny_obj_loader.h"

class Mesh {

public:
    Mesh();
    Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices);

    ~Mesh();

    void draw() const;

private:
    unsigned int m_vao{};		// Vertex Array Object
    unsigned int m_vbo{};		// Vertex Buffer Object
    unsigned int m_ibo{};		// Index Buffer Object
    int m_size{};				// Index Size

    std::vector<Vertex> m_vertices{};
    std::vector<unsigned int> m_indices{};

    void generateMesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices);
    void generateMesh(const LoadedModel& model);
};


#endif //SUPEREPIKGAME_MESH_H
