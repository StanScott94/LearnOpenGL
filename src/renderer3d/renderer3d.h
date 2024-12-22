#pragma once

#include "engine.h"
#include "../shader/shader.h"
#include "../window/window.h"

#define DEFAULT_MAX_BATCH_QUAD_COUNT 100 * 100

struct Renderer3DVertexData {
    glm::vec3 position;
    glm::vec4 color;
};

struct Renderer3DBatch {
    unsigned int vao;
    unsigned int vbo;
    unsigned int ibo;

    unsigned int vertex_count = 0;

    unsigned int texture_id = 0;

    Renderer3DVertexData *vertex_data;
    Renderer3DVertexData *vertex_data_pointer = vertex_data;
};

class Renderer3D {

public:
    Renderer3D(Shader &shader, WindowData *windowData, int maxBatchQuadCount = DEFAULT_MAX_BATCH_QUAD_COUNT);
    ~Renderer3D();

    bool Create();
    void Destroy();

    void Start();
    void End();

    void DrawQuad(glm::vec2 position, glm::vec2 scale, glm::vec4 color);

    void DrawImGui();

private:
    Shader &m_Shader;

    glm::mat4 m_ProjectionMatrix;
    glm::mat4 m_ViewMatrix;

    WindowData *m_WindowData;

    const int m_MaxBatchVertexCount;

    int m_TotalBatchCount;
    int m_TotalVertexCount;

    unsigned int m_Vao;
    unsigned int m_Vbo;
    unsigned int m_Ibo;
    unsigned int m_VertexCount;

    Renderer3DVertexData *m_VertexData;
    Renderer3DVertexData *m_VertexDataPointer;

    void DrawBatch();
};
