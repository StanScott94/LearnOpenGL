#include <stdio.h>

#include "engine.h"
#include "gl_utils.h"

#include "./shader/shader.h"
#include "./window/window.h"
#include "./renderer2d/renderer2d.h"

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

int main() {
    Window window("Learn OpenGL", SCR_WIDTH, SCR_HEIGHT, true);
    window.Create();

    Shader shader("Basic", "shaders/basic.vert", "shaders/basic.frag");
    if (!shader.Create()) {
        return 1;
    }

    Renderer2D renderer(shader, window.GetDataPointer(), 100);
    renderer.Create();

    // Setup ImGui 

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    ImGui::StyleColorsDark();

    ImGui_ImplGlfw_InitForOpenGL(window.GetGlfwWindow(), true);
    ImGui_ImplOpenGL3_Init("#version 130");

    bool show_demo_window = true;

    while (!window.ShouldClose()) {
        glClear(GL_COLOR_BUFFER_BIT);

        renderer.Start();
        
        for (int i = 0; i < 1000; i++) {
            float x = (float)rand()/(float)(RAND_MAX);
            float y = (float)rand()/(float)(RAND_MAX);
            renderer.DrawQuad(glm::vec2(x * window.GetSize().x, y * window.GetSize().y), glm::vec2(10.0f, 10.0f), glm::vec4(x, y * 0.5f, 0.2f, 1.0f));
        }

        renderer.End();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        renderer.DrawImGui();

        if (show_demo_window) {
            ImGui::ShowDemoWindow(&show_demo_window);
        }

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        window.Update();
    }

    renderer.Destroy();
    shader.Destroy();
    window.Destroy();
}