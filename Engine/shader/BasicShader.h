//
// Created by Bram on 02/12/2024.
//

#ifndef SUPEREPIKGAME_BASICSHADER_H
#define SUPEREPIKGAME_BASICSHADER_H

#include "Shader.h"

class BasicShader : public Shader
{

public:
    static BasicShader* getInstance()
    {
        static BasicShader instance;
        return &instance;
    }

    void updateUniforms(Transform& transform, Model& model, RenderingEngine* renderingEngine);

private:
    BasicShader();

};


#endif //SUPEREPIKGAME_BASICSHADER_H
