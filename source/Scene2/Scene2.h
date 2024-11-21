//
// Created by Bram on 18/11/2024.
//

#ifndef OPENGLTEMPLATE_SCENE2_H
#define OPENGLTEMPLATE_SCENE2_H

#include "glad/glad.h"


#include <array>
#include <vector>

#include "../Scene.h"
#include "../DataTypes.h"
#include "../Shader.h"
#include "../Camera.h"
#include "../Texture.h"
#include "../Mesh.h"


class Scene2 : public Scene {
public:
    Scene2();

    virtual ~Scene2() override;

    void ProcessInput(GLFWwindow *window, double deltaTime) override;

    void ProcessMouseInput(GLFWwindow *window, double xpos, double ypos) override;

    void ProcessScrollInput(GLFWwindow *window, double xoffset, double yoffset) override;

    void Render() override;

    void Update(double deltaTime) override;

    void ImGuiRender() override;

private:

    //Array of Vertex, cube 6 faces

    bool rotateX{false};
    bool rotateY{false};
    bool rotateZ{false};

    float rotateSpeedX{ 1.0f };
    float rotateSpeedY{ 1.0f };
    float rotateSpeedZ{ 1.0f };
    //Shader
    Shader *shader = nullptr;
    Mesh *mesh = nullptr;

    Texture texture;

    Camera m_camera;

    glm::vec3 modelPosition{glm::vec3(0.0f, 0.0f, 0.0f)};
    glm::vec3 modelRotation{glm::vec3(0.0f, 0.0f, 0.0f)};
    float modelScale{1.0f};
};


#endif //OPENGLTEMPLATE_SCENE2_H
