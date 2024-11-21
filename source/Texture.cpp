//
// Created by Bram on 19/11/2024.
//

#include "Texture.h"
#include "imgui.h"

#include <glad/glad.h>
#include <iostream>
#include <filesystem>


Texture::Texture() {
}

Texture::~Texture() {
    glDeleteTextures(1, &texture);
}

void Texture::LoadTexture(const std::string& path) {
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    // Set the texture wrapping/filtering options (on the currently bound texture object)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// Set texture wrapping to GL_REPEAT (usually basic wrapping method)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // Set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); // Set texture filtering to GL_LINEAR (usually basic linear filtering)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // Load and generate the texture

    unsigned char *data = stbi_load(path.c_str(), &width, &height, &nrChannels, 0);
    if (data)
    {
        if (nrChannels == 3) {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        } else if (nrChannels == 4) {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        }
        glGenerateMipmap(GL_TEXTURE_2D);

        std::filesystem::path p = path;
        fileName = p.string();
    }
    else
    {
        std::cerr << "Failed to load texture" << std::endl;
        std::cerr << "Loading Fallback texture" << std::endl;

        data = stbi_load("resources/TextureNotFound.jpg", &width, &height, &nrChannels, 0);
        if (data) {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);
        } else {
            std::cerr << "Failed to load fallback texture" << std::endl;
            std::cerr << "Insane Panic right now" << std::endl;
        }
    }
    stbi_image_free(data);

    textureLoaded = true;
}

void Texture::BindTexture() const {
    glBindTexture(GL_TEXTURE_2D, texture);
}

void Texture::UnbindTexture() const {
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::DrawImGui() {
    //Draw the texture in a new window
    if(!textureLoaded) {
        ImGui::Begin("Texture", nullptr, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoResize);
        ImGui::Text("Texture not loaded");
        ImGui::End();
        return;
    }
    std::filesystem::path p = fileName;
    std::string ActualFileName = "Texture: " + p.filename().string();
    ImGui::Begin(ActualFileName.c_str(), nullptr, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoResize);
    //Opengl
    ImGui::Text("Texture ID: %d", texture);
    ImGui::Text("Texture Width: %d", width);
    ImGui::Text("Texture Height: %d", height);
    //Open in explorer button
    if(ImGui::Button("Open in Explorer")) {
        std::filesystem::path p = fileName;
        std::string path = p.parent_path().string();
        std::cout << "Opening in explorer: " << path << std::endl;
        std::string command = "explorer " + path;
        system(command.c_str());
    }

    ImGui::Image((ImTextureID)(intptr_t)texture, ImVec2(200, 200));

    ImGui::End();
}
