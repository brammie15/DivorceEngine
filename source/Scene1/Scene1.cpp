//
// Created by Bram on 18/11/2024.
//

#include "Scene1.h"

#include <iostream>

#define STB_IMAGE_IMPLEMENTATION
#include "../stb_image.h"

#include "imgui.h"
#include "../utils.h"


Scene1::Scene1() {

    Utils::ParseOBJ("resources/cube.obj", m_lightBulbVertices, m_lightBulbIndices, false);

    Utils::ParseOBJ("resources/cube.obj", m_cubeVertices, m_cubeIndices, false);

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, m_lightBulbVertices.size() * sizeof(Vertex), m_lightBulbVertices.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_lightBulbVertices.size() * sizeof(uint32_t), m_lightBulbIndices.data(), GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *) offsetof(Vertex, position));
    glEnableVertexAttribArray(0);

    // texture coord attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *) offsetof(Vertex, texCoords));
    glEnableVertexAttribArray(1);



    glGenBuffers(1, &lightCubeVAO);
    glBindBuffer(GL_ARRAY_BUFFER, lightCubeVAO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(m_lightBulbVertices), m_lightBulbVertices.data(), GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *) offsetof(Vertex, position));
    glEnableVertexAttribArray(0);

    lightTexture.LoadTexture("resources/light.jpg");

//    shader = new Shader("shaders/solidColorObject.vert", "shaders/solidColorObject.frag");

    shader = new Shader("shaders/TexturedObjectShader.vert", "shaders/TexturedObjectShader.frag");
//    shader = new Shader("shaders/solidColorObject.vert", "shaders/solidColorObject.frag");

    lightCubeShader = new Shader("shaders/light_cube.vert", "shaders/light_cube.frag");

}

void Scene1::ProcessInput(GLFWwindow *window, double deltaTime) {
    m_camera.ProcessInput(window, deltaTime);
}

void Scene1::Render() {
    shader->use();

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, modelPosition);
    model = glm::rotate(model, glm::radians(modelRotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
    model = glm::rotate(model, glm::radians(modelRotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
    model = glm::rotate(model, glm::radians(modelRotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
    model = glm::scale(model, glm::vec3(modelScale));

    shader->setMat4("model", model);

    glm::mat4 view = m_camera.GetViewMatrix();
    shader->setMat4("view", view);

    glm::mat4 projection;
    int width, height;
    glfwGetFramebufferSize(glfwGetCurrentContext(), &width, &height);
    projection = m_camera.GetProjectionMatrix(width, height);
    shader->setMat4("projection", projection);

    shader->setVec3("aColor", glm::vec3(1.0f, 0.0f, 1.0f));

    glActiveTexture(GL_TEXTURE0);
    lightTexture.BindTexture();

    glBindVertexArray(VAO);


    int amount = m_lightBulbIndices.size();
    glDrawElements(GL_TRIANGLES, amount, GL_UNSIGNED_INT, 0);
}

void Scene1::Update(double deltaTime) {

}

Scene1::~Scene1() {
    delete shader;
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
}

void Scene1::ImGuiRender() {
    ImGui::Begin("Model Position", nullptr, ImGuiWindowFlags_AlwaysAutoResize);

    ImGui::Text("Model Scale");
    ImGui::DragFloat("Scale", &modelScale, 0.01f, 0);
    ImGui::Separator();

    ImGui::Text("Model Position");
    ImGui::DragFloat("X", &modelPosition.x, 0.1f);
    ImGui::DragFloat("Y", &modelPosition.y, 0.1f);
    ImGui::DragFloat("Z", &modelPosition.z, 0.1f);
    ImGui::Separator();

    ImGui::Text("Model Rotation");
    ImGui::DragFloat("X Rotation", &modelRotation.x, 0.1f);
    ImGui::DragFloat("Y Rotation", &modelRotation.y, 0.1f);
    ImGui::DragFloat("Z Rotation", &modelRotation.z, 0.1f);

    ImGui::End();


}

void Scene1::ProcessMouseInput(GLFWwindow *window, double xpos, double ypos) {
    m_camera.ProcessMouseInput(xpos, ypos);

}

void Scene1::ProcessScrollInput(GLFWwindow *window, double xoffset, double yoffset) {

}
