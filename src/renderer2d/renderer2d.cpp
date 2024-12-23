#include "renderer2d.h"
#include "gl_utils.h"

#include "../shader/shader.h"

Renderer2D::Renderer2D(Shader &shader): m_Shader(shader) {
}

Renderer2D::~Renderer2D() {
}

bool Renderer2D::Create() {
    float vertices[] = {
        // positions         // colors
         0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,  // bottom right
        -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,  // bottom left
         0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f   // top 
    };

    GL(glGenVertexArrays(1, &m_Vao));
    GL(glGenBuffers(1, &m_Vbo));
    GL(glBindVertexArray(m_Vao));

    GL(glBindBuffer(GL_ARRAY_BUFFER, m_Vbo));
    GL(glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW));

    // position attribute
    GL(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0));
    GL(glEnableVertexAttribArray(0));

    // color attribute
    GL(glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float))));
    GL(glEnableVertexAttribArray(1));

    return true;
}

void Renderer2D::Destroy() {
    GL(glDeleteBuffers(1, &m_Vbo));
    GL(glDeleteVertexArrays(1, &m_Vao));
}

void Renderer2D::Draw() {
    m_Shader.Bind();
    glBindVertexArray(m_Vao);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    m_Shader.Unbind();

    GL(glBindBuffer(GL_ARRAY_BUFFER, 0));
}

void Renderer2D::DrawImGui() {
#ifdef DEBUG
    ImGui::Begin("Renderer 2D");
    ImGui::Text("FPS: %f", ImGui::GetIO().Framerate);
    ImGui::End();
#endif
}
