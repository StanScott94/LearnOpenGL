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
    Shader &m_Shader;
    Window &m_Window;
    unsigned int m_Vao;
    unsigned int m_Vbo;
    void ProcessInput(GLFWwindow *window);
};
