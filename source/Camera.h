//
// Created by Bram on 19/11/2024.
//

#ifndef OPENGLTEMPLATE_CAMERA_H
#define OPENGLTEMPLATE_CAMERA_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "GLFW/glfw3.h"


class Camera {
public:
    Camera();
    void ProcessInput(GLFWwindow *window, double deltaTime);
    glm::mat4 GetViewMatrix();
    glm::mat4 GetProjectionMatrix(float width, float height) const;

    glm::vec3 GetCameraPos() const;
    glm::vec3 GetCameraFront() const;
    glm::vec3 GetCameraUp() const;

    void ProcessImGui();


    void ProcessMouseInput(double xPosIn, double yPosIn);

    void ProcessScrollInput(double scroll);

private:
    glm::vec3 cameraPos   = glm::vec3(0.0f, 0.0f, 3.0f);
    glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
    glm::vec3 cameraUp    = glm::vec3(0.0f, 1.0f, 0.0f);

    bool firstMouse = true;
    float yaw   = -90.0f;	// yaw is initialized to -90.0 degrees since a yaw of 0.0 results in a direction vector pointing to the right so we initially rotate a bit to the left.
    float pitch =  0.0f;
    float lastX =  800.0f / 2.0;
    float lastY =  600.0 / 2.0;
    float fov   =  45.0f;

    float speed = 0.05f;
};


#endif //OPENGLTEMPLATE_CAMERA_H
