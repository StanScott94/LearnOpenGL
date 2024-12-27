#pragma once

#include "engine.h"
#include "../window/window.h"
#include "../shader/shader.h"

class Renderer {
public:
    Renderer(Shader &shader, Window &window);
    ~Renderer();

    bool Create();
    void Destroy();
    void Draw();
    void DrawImGui();

private:
    Shader &shader;
    Window &window;
    unsigned int vao;
    unsigned int vbo;
    void ProcessInput(GLFWwindow *window);
};
