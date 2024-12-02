#ifndef SUPEREPIKGAME_RENDERINGENGINE_H
#define SUPEREPIKGAME_RENDERINGENGINE_H



#include "Window.h"
#include "scenegraph/Node.h"
#include "components/camera/Camera.h"
#include <glad/glad.h>

class Node;
class Font;

class RenderingEngine {

public:
    RenderingEngine();
    //RenderingEngine(Window& window);
    virtual ~RenderingEngine() {};

    void init();
    void render(Node* rootNode);

    inline Camera& getMainCamera() { return *m_mainCamera; }
    inline void addCamera(Camera* camera) { m_mainCamera = camera; }

private:
    //Window* m_window;
    Camera* m_mainCamera;
    Font* font;

};

#endif //SUPEREPIKGAME_RENDERINGENGINE_H
