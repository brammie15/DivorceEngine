//
// Created by Bram on 18/11/2024.
//

#include <iostream>
#include <algorithm>
#include "Scene2.h"

#include "stb_image.h"

#include "../utils.h"

#include "imgui.h"

Scene2::Scene2() {
    texture = Texture();
    texture.LoadTexture("resources/vehicle_diffuse.jpg");
    texture.type = "texture_diffuse";

    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    Utils::ParseOBJ("resources/vehicle.obj", vertices, indices, false);
    std::vector<Texture> textures;
    textures.push_back(texture);

    mesh = new Mesh(vertices, indices, textures);

//    shader = new Shader("shaders/solidColorObject.vert", "shaders/solidColorObject.frag");

    shader = new Shader("shaders/meshShader.vert", "shaders/meshShader.frag");

}

void Scene2::ProcessInput(GLFWwindow *window, double deltaTime) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }

    m_camera.ProcessInput(window, deltaTime);
}

void Scene2::Render() {
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

//    texture.BindTexture();

    mesh->Draw(*shader);



}

void Scene2::Update(double deltaTime) {

    if(rotateX){
        modelRotation.x += static_cast<double>(rotateSpeedX) * deltaTime;
    }
    if(rotateY){
        modelRotation.y += static_cast<double>(rotateSpeedY) * deltaTime;
    }
    if(rotateZ){
        modelRotation.z += static_cast<double>(rotateSpeedZ) * deltaTime;
    }

}

Scene2::~Scene2() {
    delete shader;
}

void Scene2::ImGuiRender() {
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

    ImGui::Separator();
    ImGui::Text("Start/Stop Rotation");
    //CheckBox, Speed layout
    ImGui::Checkbox("Rotate X", &rotateX);
    ImGui::SameLine();
    ImGui::DragFloat("Speed X", &rotateSpeedX, 1, -FLT_MAX, +FLT_MAX);

    ImGui::Checkbox("Rotate Y", &rotateY);
    ImGui::SameLine();
    ImGui::DragFloat("Speed Y", &rotateSpeedY, 1, -FLT_MAX, +FLT_MAX);

    ImGui::Checkbox("Rotate Z", &rotateZ);
    ImGui::SameLine();
    ImGui::DragFloat("Speed Z", &rotateSpeedZ, 1, -FLT_MAX, +FLT_MAX);

    ImGui::End();

    m_camera.ProcessImGui();

//    texture.DrawImGui();
}

void Scene2::ProcessMouseInput(GLFWwindow *window, double xpos, double ypos) {
    //if the mouse is locked

    if(glfwGetInputMode(window, GLFW_CURSOR) == GLFW_CURSOR_DISABLED){
        m_camera.ProcessMouseInput(xpos, ypos);
    }
}

void Scene2::ProcessScrollInput(GLFWwindow *window, double xoffset, double yoffset) {
    m_camera.ProcessScrollInput(yoffset);
}
