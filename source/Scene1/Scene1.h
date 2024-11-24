//
// Created by Bram on 18/11/2024.
//

#ifndef OPENGLTEMPLATE_SCENE1_H
#define OPENGLTEMPLATE_SCENE1_H

#include "glad/glad.h"

#include <array>
#include <vector>

#include "Scene.h"
#include "DataTypes.h"
#include "Shader.h"
#include "Camera.h"
#include "Texture.h"


class Scene1 : public Scene {
public:
    Scene1();
    virtual ~Scene1();
    void ProcessInput(GLFWwindow *window, double deltaTime) override;
    void ProcessMouseInput(GLFWwindow *window, double xpos, double ypos) override;
    void ProcessScrollInput(GLFWwindow *window, double xoffset, double yoffset) override;
    void Render() override;
    void Update(double deltaTime) override;
    void ImGuiRender() override;

private:

    std::vector<Vertex> m_lightBulbVertices;
    std::vector<uint32_t> m_lightBulbIndices;

    std::vector<Vertex> m_cubeVertices;
    std::vector<uint32_t> m_cubeIndices;

    Camera m_camera;

    unsigned int VBO, VAO, EBO;
    unsigned int lightCubeVAO;

    //Shader
    Shader* shader = nullptr;
    Shader* lightCubeShader = nullptr;

    //Texture
    Texture lightTexture;

    glm::vec3 modelPosition = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec3 modelRotation = glm::vec3(0.0f, 0.0f, 0.0f);
    float modelScale = 1.0f;
};


#endif //OPENGLTEMPLATE_SCENE1_H
