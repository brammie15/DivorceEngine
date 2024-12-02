//
// Created by Bram on 25/11/2024.
//

#include <iostream>
#include "ResourceManager.h"

std::shared_ptr<Texture> ResourceManager::LoadTexture(const std::string &path) {

    std::cout << "Loading texture: " << path << std::endl;

    if (textures.find(path) == textures.end()) {
        textures[path] = std::make_unique<Texture>();
        textures[path]->LoadTexture(path);
    }
    return textures[path];
}
