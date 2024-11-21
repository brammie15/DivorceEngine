//
// Created by Bram on 18/11/2024.
//

#ifndef OPENGLTEMPLATE_UTILS_H
#define OPENGLTEMPLATE_UTILS_H

#include <string>
#include <fstream>
#include <vector>
#include <glm/glm.hpp>
#include "DataTypes.h"

namespace Utils {
    static float cross(const glm::vec2& u, const glm::vec2& v) {
        return u.x * v.y - u.y * v.x;
    }


    static bool ParseOBJ(const std::string& filename, std::vector<Vertex>& vertices, std::vector<uint32_t>& indices, bool flipAxisAndWinding = true)
    {
        std::ifstream file(filename);
        if (!file)
            return false;

        std::vector<glm::vec3> positions{};
        std::vector<glm::vec3> normals{};
        std::vector<glm::vec2> UVs{};

        vertices.clear();
        indices.clear();

        std::string sCommand;
        // start a while iteration ending when the end of file is reached (ios::eof)
        while (!file.eof())
        {
            //read the first word of the string, use the >> operator (istream::operator>>)
            file >> sCommand;
            //use conditional statements to process the different commands
            if (sCommand == "#")
            {
                // Ignore Comment
            }
            else if (sCommand == "v")
            {
                //Vertex
                float x, y, z;
                file >> x >> y >> z;

                positions.emplace_back(x, y, z);
            }
            else if (sCommand == "vt")
            {
                // Vertex TexCoord
                float u, v;
                file >> u >> v;
                UVs.emplace_back(u, 1 - v);
            }
            else if (sCommand == "vn")
            {
                // Vertex Normal
                float x, y, z;
                file >> x >> y >> z;

                normals.emplace_back(x, y, z);
            }
            else if (sCommand == "f")
            {
                //if a face is read:
                //construct the 3 vertices, add them to the vertex array
                //add three indices to the index array
                //add the material index as attibute to the attribute array
                //
                // Faces or triangles
                Vertex vertex{};
                size_t iPosition, iTexCoord, iNormal;

                uint32_t tempIndices[3];
                for (size_t iFace = 0; iFace < 3; iFace++)
                {
                    // OBJ format uses 1-based arrays
                    file >> iPosition;
                    vertex.position = positions[iPosition - 1];

                    if ('/' == file.peek())//is next in buffer ==  '/' ?
                    {
                        file.ignore();//read and ignore one element ('/')

                        if ('/' != file.peek())
                        {
                            // Optional texture coordinate
                            file >> iTexCoord;
                            vertex.texCoords = UVs[iTexCoord - 1];
                        }

                        if ('/' == file.peek())
                        {
                            file.ignore();

                            // Optional vertex normal
                            file >> iNormal;
                            vertex.normal = normals[iNormal - 1];
                        }
                    }

                    vertices.push_back(vertex);
                    tempIndices[iFace] = uint32_t(vertices.size()) - 1;
                    //indices.push_back(uint32_t(vertices.size()) - 1);
                }

                indices.push_back(tempIndices[0]);
                if (flipAxisAndWinding)
                {
                    indices.push_back(tempIndices[2]);
                    indices.push_back(tempIndices[1]);
                }
                else
                {
                    indices.push_back(tempIndices[1]);
                    indices.push_back(tempIndices[2]);
                }
            }
            //read till end of line and ignore all remaining chars
            file.ignore(1000, '\n');
        }

        //Cheap Tangent Calculations
        for (uint32_t i = 0; i < indices.size(); i += 3)
        {
            uint32_t index0 = indices[i];
            uint32_t index1 = indices[size_t(i) + 1];
            uint32_t index2 = indices[size_t(i) + 2];

            const glm::vec3& p0 = vertices[index0].position;
            const glm::vec3& p1 = vertices[index1].position;
            const glm::vec3& p2 = vertices[index2].position;
            const glm::vec2& uv0 = vertices[index0].texCoords;
            const glm::vec2& uv1 = vertices[index1].texCoords;
            const glm::vec2& uv2 = vertices[index2].texCoords;

            const glm::vec3 edge0 = p1 - p0;
            const glm::vec3 edge1 = p2 - p0;
            const glm::vec2 diffX = glm::vec2(uv1.x - uv0.x, uv2.x - uv0.x);
            const glm::vec2 diffY = glm::vec2(uv1.y - uv0.y, uv2.y - uv0.y);
            float r = 1.f / cross(diffX, diffY);

            glm::vec3 tangent = (edge0 * diffY.y - edge1 * diffY.x) * r;
            vertices[index0].tangent += tangent;
            vertices[index1].tangent += tangent;
            vertices[index2].tangent += tangent;
        }

        //Fix the tangents per vertex now because we accumulated
        for (auto& v : vertices)
        {
            //Rejection of v.tangent and v.normal
//            v.tangent = glm::normalize(glm::reject(v.tangent, v.normal));


//            v.tangent = Vector3::Reject(v.tangent, v.normal).Normalized();

            v.tangent = v.tangent - (glm::abs(glm::dot(v.tangent, v.normal)) * v.normal);

            if(flipAxisAndWinding)
            {
                v.position.z *= -1.f;
                v.normal.z *= -1.f;
                v.tangent.z *= -1.f;
            }

        }

        return true;
    }
};

#endif //OPENGLTEMPLATE_UTILS_H
