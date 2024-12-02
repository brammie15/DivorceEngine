#ifndef SUPEREPIKGAME_RENDERER_H
#define SUPEREPIKGAME_RENDERER_H

#include "../Component.h"
#include "../model/Model.h"
#include "../../shader/Shader.h"

class Shader;

class Renderer : public Component
{
public:
    Renderer(Model* model, Shader* shader);
    virtual ~Renderer() {}

    //virtual void render();
    virtual void render(RenderingEngine* renderingEngine);


private:
    Model* m_model;
    Shader* m_shader;
};


#endif //SUPEREPIKGAME_RENDERER_H
