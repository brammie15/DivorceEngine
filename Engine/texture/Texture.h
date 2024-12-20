#ifndef OPENGLTEMPLATE_TEXTURE_H
#define OPENGLTEMPLATE_TEXTURE_H
#include <glad/glad.h>
#include <string>
#include <iostream>

class Texture {

public:
    Texture() {};
    Texture(const char* fileName);
    ~Texture();

    void bind() const;
    void unbind() const;

    int getTextureID();

private:
    unsigned int m_textureID;
    unsigned char* m_data;

    int m_width;
    int m_height;
    int m_nrChannels;

    GLenum m_textureTarget;

    static const Texture* s_lastBind;

};

#endif //OPENGLTEMPLATE_TEXTURE_H
