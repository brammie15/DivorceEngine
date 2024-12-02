#ifndef SUPEREPIKGAME_TESTGAME_H
#define SUPEREPIKGAME_TESTGAME_H


#pragma once

#include "../engine/core/Game.h"
#include "../Engine/scenegraph/Node.h"
#include "../engine/texture/Texture.h"
#include "../engine/shader/Shader.h"

class TestGame : public Game {

public:
    TestGame() {}

    void init(RenderingEngine* renderingEngine);
    void update(float delta);
    void render(RenderingEngine* renderingEngine) override;

private:
    Node* cubeNodeTest;
    Node* cubeNodeTest2;
    Node* cubeNodeTest3;

    RenderingEngine* m_renderingEngine;
};


#endif //SUPEREPIKGAME_TESTGAME_H
