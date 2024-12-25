#include "camera/camera.h"
#include "engine.h"
#include "./window/window.h"
#include "./shader/shader.h"
#include "./renderer/renderer.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

int main() {
    Window window("Learn OpenGL", SCR_WIDTH, SCR_HEIGHT, true);
    window.Create();

    Shader shader("Basic", "shaders/basic.vert", "shaders/basic.frag");
    if (!shader.Create()) {
        return 1;
    }

    Renderer renderer(shader, window);
    renderer.Create();

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui::StyleColorsDark();

    ImGui_ImplGlfw_InitForOpenGL(window.GetGlfwWindow(), true);

    #ifdef __APPLE__
        ImGui_ImplOpenGL3_Init("#version 150");
    #else
        ImGui_ImplOpenGL3_Init("#version 130");
    #endif

    while (!window.ShouldClose()) {
        glClearColor(0.2f, 0.0f, 0.2f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        renderer.Draw();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        renderer.DrawImGui();

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        window.Update();
    }

    shader.Destroy();
    window.Destroy();
}

