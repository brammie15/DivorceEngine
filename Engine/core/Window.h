#ifndef SUPEREPIKGAME_WINDOW_H
#define SUPEREPIKGAME_WINDOW_H

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

class Window {

public:

    Window() {}
    ~Window() {}

    void create(int width, int height, const char* title);
    bool isCloseRequested();
    static void clear();
    void update();
    void render();
    void dispose();

    static GLFWwindow* getWindow();
    static int getWidth();
    static int getHeight();


private:
    static GLFWwindow* m_window;
    static int m_width;
    static int m_height;
    const char* m_title;
};


#endif //SUPEREPIKGAME_WINDOW_H
