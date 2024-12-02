#include <iostream>

#define GLFW_INCLUDE_NONE

#include "glad/glad.h"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "imgui_internal.h"

#include "Scene1/Scene1.h"
#include "Scene2/Scene2.h"


struct WindowData {
    Scene *scene;
    double deltaTime;

};

void ProcessInput(GLFWwindow *window) {

    WindowData *windowData = reinterpret_cast<WindowData *>(glfwGetWindowUserPointer(window));




    //Lock mouse
    if (glfwGetKey(window, GLFW_KEY_M) == GLFW_PRESS) {
        if (glfwGetInputMode(window, GLFW_CURSOR) == GLFW_CURSOR_NORMAL) {
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        } else {
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        }
    }


    windowData->scene->ProcessInput(window, windowData->deltaTime);

}

void ProcessScrollInput(GLFWwindow *window, double xoffset, double yoffset) {
    WindowData *windowData = reinterpret_cast<WindowData *>(glfwGetWindowUserPointer(window));
    windowData->scene->ProcessScrollInput(window, xoffset, yoffset);
}

static void glfw_error_callback(int error, const char *description) {
    fprintf(stderr, "GLFW Error %d: %s\n", error, description);
}

void MouseCallback(GLFWwindow *window, double xpos, double ypos) {
    ImGui_ImplGlfw_CursorPosCallback(window, xpos, ypos);

    ImGuiIO &io = ImGui::GetIO();
    if (io.WantCaptureMouse) {
        return;
    }

    auto *windowData = reinterpret_cast<WindowData *>(glfwGetWindowUserPointer(window));
    windowData->scene->ProcessMouseInput(window, xpos, ypos);
}

int main() {
    glfwSetErrorCallback(glfw_error_callback);

    if (!glfwInit()) {
        std::cout << "Failed to initialize GLFW\n";
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Construct the window
    GLFWwindow *window = glfwCreateWindow(800, 600, "OpenGL Template", nullptr, nullptr);
    if (!window) {
        std::cout << "Failed to create the GLFW window\n";
        glfwTerminate();
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);
    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    (void) io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;         // Enable Docking
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;       // Enable Multi-Viewport / Platform Windows
    //io.ConfigViewportsNoAutoMerge = true;
//    io.ConfigViewportsNoTaskBarIcon = true;

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    //ImGui::StyleColorsLight();

    // When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
    ImGuiStyle &style = ImGui::GetStyle();
    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
        style.WindowRounding = 0.0f;
        style.Colors[ImGuiCol_WindowBg].w = 1.0f;
    }

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 130");

    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD\n";
        return -1;
    }

    // Handle view port dimensions
    glViewport(0, 0, 800, 600);
    glfwSetFramebufferSizeCallback(window, [](GLFWwindow *window, int width, int height) {
        glViewport(0, 0, width, height);
    });

    glfwSetWindowFocusCallback(window, [](GLFWwindow *window, int focused) {
        if (focused) {
            for (int i = 0; i < ImGui::GetCurrentContext()->Windows.Size; i++) {
                ImGuiWindow *window = ImGui::GetCurrentContext()->Windows[i];
                if (window->WasActive) {
                    ImGui::SetWindowFocus(window->Name); //Doesnt work on OS
                }
            }
        }
    });
    glfwSetCursorPosCallback(window, MouseCallback);
    glfwSetScrollCallback(window, [](GLFWwindow *window, double xoffset, double yoffset) {
        ProcessScrollInput(window, xoffset, yoffset);
    });


    glEnable(GL_DEPTH_TEST);

    Scene *pScene = new Scene2();

    WindowData windowData{};
    windowData.scene = pScene;
    glfwSetWindowUserPointer(window, &windowData);

    const double fpsLimit = 1.0 / 60.0;
    double lastUpdateTime = 0;
    double lastFrameTime = 0;

    double fpsCounter = 0;
    const double fpsUpdateInterval = 1.0;

    // This is the render loop
    while (!glfwWindowShouldClose(window)) {

        double now = glfwGetTime();
        double delta = now - lastUpdateTime;
        windowData.deltaTime = delta;

        glfwPollEvents();
        if (glfwGetWindowAttrib(window, GLFW_ICONIFIED) != 0) {
            ImGui_ImplGlfw_Sleep(10);
            continue;
        }
        ProcessInput(window);

        pScene->Update(delta);

        fpsCounter += delta;
        if (fpsCounter >= fpsUpdateInterval) {
            std::cout << "FPS: " << 1.0 / delta << std::endl;
            fpsCounter = 0;
        }

        if ((now - lastFrameTime) >= fpsLimit) {

            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplGlfw_NewFrame();
            ImGui::NewFrame();


            pScene->ImGuiRender();

//            const float windowWidth = ImGui::GetContentRegionAvail().x;
//            const float windowHeight = ImGui::GetContentRegionAvail().y;
//
//            sceneBuffer.RescaleFrameBuffer(windowWidth, windowHeight);
//
//            ImVec2 pos = ImGui::GetCursorScreenPos();
//
//            ImGui::GetWindowDrawList()->AddImage(
//                    reinterpret_cast<ImTextureID>((void *) sceneBuffer.getFrameTexture()),
//                    pos,
//                    ImVec2(pos.x + windowWidth, pos.y + windowHeight),
//                    ImVec2(0, 1),
//                    ImVec2(1, 0)
//                    );

            ImGui::EndFrame();
            ImGui::Render();

            int w, h;
            glfwGetFramebufferSize(window, &w, &h);
            glViewport(0, 0, w, h);
            glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            pScene->Render();

            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

            if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
                GLFWwindow *backup_current_context = glfwGetCurrentContext();
                ImGui::UpdatePlatformWindows();
                ImGui::RenderPlatformWindowsDefault();
                glfwMakeContextCurrent(backup_current_context);
            }

            glfwSwapBuffers(window);

            lastFrameTime = now;
        }

        lastUpdateTime = now;
    }

    delete pScene;

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}