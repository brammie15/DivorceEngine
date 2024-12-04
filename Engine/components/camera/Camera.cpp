#include "Camera.h"
#include "../../core/InputHandler.h"
#include "../../core/RenderingEngine.h"

Camera::Camera(float fov, float aspect, float zNear, float zFar) :
        m_fov(fov),
        m_aspect(aspect),
        m_zNear(zNear),
        m_zFar(zFar),
        m_projectionMatrix(glm::perspective(fov, aspect, zNear, zFar)),
        m_sensitivity(0.005f) {

}

void Camera::input(float delta) {
    if (glfwGetKey(Window::getWindow(), GLFW_KEY_W) == GLFW_PRESS) {
        getTransform().getPos().z += delta;
    }
    if (glfwGetKey(Window::getWindow(), GLFW_KEY_S) == GLFW_PRESS) {
        getTransform().getPos().z -= delta;
    }
    if (glfwGetKey(Window::getWindow(), GLFW_KEY_A) == GLFW_PRESS) {
        getTransform().getPos().x -= delta;
    }
    if (glfwGetKey(Window::getWindow(), GLFW_KEY_D) == GLFW_PRESS) {
        getTransform().getPos().x += delta;
    }

    if (glfwGetKey(Window::getWindow(), GLFW_KEY_O) == GLFW_PRESS) {
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }
    if (glfwGetKey(Window::getWindow(), GLFW_KEY_P) == GLFW_PRESS) {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    }
    if (glfwGetKey(Window::getWindow(), GLFW_KEY_L) == GLFW_PRESS) {
        glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
    }


    if (InputHandler::getLockStatus() == true) {
        std::cout << InputHandler::getLockStatus() << std::endl;

        //Camera Rotation
        glm::vec2 delta = InputHandler::getCursorPosition() - InputHandler::getLockedCursorPosition();
        InputHandler::setCursorPosition(Window::getWindow(), InputHandler::getLockedCursorPosition());

        getTransform().rotate(glm::vec3(0, 1, 0), -delta.x * m_sensitivity / 100.f);
        getTransform().rotate(getTransform().getRight(), delta.y * m_sensitivity / 100.f);
    }
}

glm::mat4 Camera::getViewMatrix() {
    glm::vec3 position = getTransform().getPos();
    glm::vec3 target = getTransform().getPos() + getTransform().getForward();
    glm::vec3 up = getTransform().getUp();

    m_viewMatrix = glm::lookAt(position, target, up);

    return m_viewMatrix;
}

// RETURN PROJECTION MATRIX
glm::mat4 Camera::getProjectionMatrix() {
    return m_projectionMatrix;
}

// RETURN VIEW * PROJECTION MATRIX
glm::mat4 Camera::getViewProjectionMatrix() {
    return m_projectionMatrix * getViewMatrix();
}

void Camera::addToRenderingEngine(RenderingEngine *renderingEngine) {
    renderingEngine->addCamera(this);
}