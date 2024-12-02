#ifndef SUPEREPIKGAME_MESH_H
#define SUPEREPIKGAME_MESH_H



#include <glad/glad.h>
#include <glm/glm.hpp>


struct Vertex {
    glm::vec3 m_position;
    glm::vec2 m_textureCoord;
    glm::vec3 m_normal;
    // TODO : add tangent
    // TODO : add bitTangent

    Vertex(glm::vec3 position = glm::vec3(0, 0, 0), glm::vec2 textureCoord = glm::vec2(0, 0), glm::vec3 normal = glm::vec3(0, 0, 0)) {
        this->m_position = position;
//        this->m_textureCoord = textureCoord;
//        this->m_normal = normal;
    }
};


#include <iostream>
#include <vector>
#include <string>

class Mesh {

public:
    Mesh();
    Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices);

    ~Mesh();

    void draw() const;

private:
    unsigned int m_vao;		// Vertex Array Object
    unsigned int m_vbo;		// Vertex Buffer Object
    unsigned int m_ibo;		// Index Buffer Object
    int m_size;				// Index Size

    std::vector<Vertex> m_vertices;
    std::vector<unsigned int> m_indices;

    void generateMesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices);
};


#endif //SUPEREPIKGAME_MESH_H
