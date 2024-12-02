//
// Created by Bram on 02/12/2024.
//

#include <iostream>
#include "core/Window.h"
#include "core/RenderingEngine.h"
#include "core/CoreEngine.h"
#include "TestGame.h"

const unsigned int WIDTH = 1600;
const unsigned int HEIGHT = 900;

const unsigned int NE_FRAMERATE = 60;

int main() {

    TestGame game;

    Window window;
    window.create(WIDTH, HEIGHT, "OpenGLTemplate");

    RenderingEngine renderEngine;

    CoreEngine engine(&window, NE_FRAMERATE, &renderEngine, &game);
    engine.start();

    return 0;
}