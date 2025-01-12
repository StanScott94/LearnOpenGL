#pragma once

#include "engine.h"
#include "../ui/window.h"

class Renderer {
public:
    Renderer(Window &window);
    ~Renderer();

    bool Create();
    void Destroy();
    void Draw();
    void DrawImGui();

private:
    Window &window;
    unsigned int vao;
    unsigned int lightVao;
    unsigned int vbo;
    void ProcessInput(GLFWwindow *window);
};
