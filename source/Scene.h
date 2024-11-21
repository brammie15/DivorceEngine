//
// Created by Bram on 18/11/2024.
//

#ifndef OPENGLTEMPLATE_SCENE_H
#define OPENGLTEMPLATE_SCENE_H


#include "GLFW/glfw3.h"

class Scene {
public:
    Scene() = default;
    virtual ~Scene() = default;

    virtual void ProcessInput(GLFWwindow *window, double deltaTime) = 0;
    virtual void ProcessMouseInput(GLFWwindow *window, double xpos, double ypos) = 0;
    virtual void ProcessScrollInput(GLFWwindow *window, double xoffset, double yoffset) = 0;
    virtual void Render() = 0;
    virtual void Update(double deltaTime) = 0;
    virtual void ImGuiRender() = 0;
private:

};


#endif //OPENGLTEMPLATE_SCENE_H
