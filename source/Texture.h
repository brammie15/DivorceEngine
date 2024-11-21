//
// Created by Bram on 19/11/2024.
//

#ifndef OPENGLTEMPLATE_TEXTURE_H
#define OPENGLTEMPLATE_TEXTURE_H

#include <string>
#include "stb_image.h"


class Texture {
public:
    Texture();
    virtual ~Texture();
    void LoadTexture(const std::string& path);
    void BindTexture() const;
    void UnbindTexture() const;

    void DrawImGui();
    std::string type{};
private:
    unsigned int texture;

    int width, height, nrChannels;

    bool textureLoaded = false;

    std::string fileName{ "Unknown" };

};

#endif //OPENGLTEMPLATE_TEXTURE_H
