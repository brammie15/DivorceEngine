//
// Created by Bram on 18/11/2024.
//

#ifndef OPENGLTEMPLATE_FRAMEBUFFER_H
#define OPENGLTEMPLATE_FRAMEBUFFER_H


// FrameBuffer.h

#pragma once
#include <iostream>
#include <glad/glad.h>
#include <glm/glm.hpp>

class FrameBuffer
{
public:
    FrameBuffer(float width, float height);
    ~FrameBuffer();
    unsigned int getFrameTexture();
    void RescaleFrameBuffer(float width, float height);
    void Bind() const;
    void Unbind() const;
private:
    unsigned int fbo;
    unsigned int texture;
    unsigned int rbo;
};



#endif //OPENGLTEMPLATE_FRAMEBUFFER_H
