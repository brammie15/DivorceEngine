//
// Created by Bram on 18/11/2024.
//

#ifndef OPENGLTEMPLATE_DATATYPES_H
#define OPENGLTEMPLATE_DATATYPES_H

#include <glm/glm.hpp>

struct Vertex {
    Vertex() {

    }

    glm::vec3 position;
    glm::vec2 texCoords;
    glm::vec3 normal;
    glm::vec3 tangent;
    glm::vec3 bitangent;

    Vertex(float x, float y, float z, float uvx, float uvy): position(x, y, z), texCoords(uvx, uvy) {}

};

#endif //OPENGLTEMPLATE_DATATYPES_H
