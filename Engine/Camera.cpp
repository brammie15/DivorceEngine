//
// Created by Bram on 19/11/2024.
//

#include "Camera.h"
#include "imgui.h"

Camera::Camera() {

}

void Camera::ProcessInput(GLFWwindow *window, double deltaTime) {
    float velocity = speed * deltaTime;
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        cameraPos += velocity * cameraFront;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        cameraPos -= velocity * cameraFront;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * velocity;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * velocity;

    if(glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
        cameraPos -= velocity * cameraUp;
    if(glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
        cameraPos += velocity * cameraUp;
}

glm::mat4 Camera::GetViewMatrix() {
    return glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
}

glm::mat4 Camera::GetProjectionMatrix(float width, float height) const {
    return glm::perspective(glm::radians(fov), width / height, 0.1f, 100.0f);
}

glm::vec3 Camera::GetCameraPos() const {
    return cameraPos;
}

glm::vec3 Camera::GetCameraFront() const {
    return cameraFront;
}

glm::vec3 Camera::GetCameraUp() const {
    return cameraUp;
}

void Camera::ProcessMouseInput(double xPosIn, double yPosIn) {
    float xpos = static_cast<float>(xPosIn);
    float ypos = static_cast<float>(yPosIn);

    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top
    lastX = xpos;
    lastY = ypos;

    float sensitivity = 0.1f; // change this value to your liking
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    yaw += xoffset;
    pitch += yoffset;

    // make sure that when pitch is out of bounds, screen doesn't get flipped
    if (pitch > 89.0f)
        pitch = 89.0f;
    if (pitch < -89.0f)
        pitch = -89.0f;

    glm::vec3 front;
    front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    front.y = sin(glm::radians(pitch));
    front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    cameraFront = glm::normalize(front);

}

void Camera::ProcessImGui() {
    //Camera data
    ImGui::Begin("Camera", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
    //Position
    ImGui::Text("Camera Position");
    ImGui::DragFloat("X", &cameraPos.x, 0.1f);
    ImGui::DragFloat("Y", &cameraPos.y, 0.1f);
    ImGui::DragFloat("Z", &cameraPos.z, 0.1f);

    //Reset to 0,0,0
    if (ImGui::Button("Reset Position")) {
        cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
    }

    //Current Speed
    ImGui::Text("Camera Speed");
    ImGui::DragFloat("Speed", &speed, 0.01f, 0);

    ImGui::End();
}

void Camera::ProcessScrollInput(double scroll) {
    //Change speed
    speed += scroll;
    if (speed < 0.01f) {
        speed = 0.01f;
    }

}


