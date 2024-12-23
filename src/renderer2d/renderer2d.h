#pragma once

#include "engine.h"
#include "../shader/shader.h"

class Renderer2D {

public:
    Renderer2D(Shader &shader);
    ~Renderer2D();

    bool Create();
    void Destroy();
    void Draw();
    void DrawImGui();

private:
    Shader &m_Shader;
    unsigned int m_Vao;
    unsigned int m_Vbo;
};
