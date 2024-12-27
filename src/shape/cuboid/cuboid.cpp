#include "cuboid.h"

Cuboid::Cuboid() {
}

Cuboid::~Cuboid() {
}

bool Cuboid::Create(float width, float length, float height) {
    float halfWidth = width / 2.0f;
    float halfLength = length / 2.0f;
    float halfHeight = height / 2.0f;

    vertices = {
        // Front face
        -halfWidth, -halfHeight, -halfLength,  0.0f, 0.0f,
         halfWidth, -halfHeight, -halfLength,  1.0f, 0.0f,
         halfWidth,  halfHeight, -halfLength,  1.0f, 1.0f,
         halfWidth,  halfHeight, -halfLength,  1.0f, 1.0f,
        -halfWidth,  halfHeight, -halfLength,  0.0f, 1.0f,
        -halfWidth, -halfHeight, -halfLength,  0.0f, 0.0f,

        // Back face
        -halfWidth, -halfHeight,  halfLength,  0.0f, 0.0f,
         halfWidth, -halfHeight,  halfLength,  1.0f, 0.0f,
         halfWidth,  halfHeight,  halfLength,  1.0f, 1.0f,
         halfWidth,  halfHeight,  halfLength,  1.0f, 1.0f,
        -halfWidth,  halfHeight,  halfLength,  0.0f, 1.0f,
        -halfWidth, -halfHeight,  halfLength,  0.0f, 0.0f,

        // Left face
        -halfWidth,  halfHeight,  halfLength,  1.0f, 0.0f,
        -halfWidth,  halfHeight, -halfLength,  1.0f, 1.0f,
        -halfWidth, -halfHeight, -halfLength,  0.0f, 1.0f,
        -halfWidth, -halfHeight, -halfLength,  0.0f, 1.0f,
        -halfWidth, -halfHeight,  halfLength,  0.0f, 0.0f,
        -halfWidth,  halfHeight,  halfLength,  1.0f, 0.0f,

        // Right face
         halfWidth,  halfHeight,  halfLength,  1.0f, 0.0f,
         halfWidth,  halfHeight, -halfLength,  1.0f, 1.0f,
         halfWidth, -halfHeight, -halfLength,  0.0f, 1.0f,
         halfWidth, -halfHeight, -halfLength,  0.0f, 1.0f,
         halfWidth, -halfHeight,  halfLength,  0.0f, 0.0f,
         halfWidth,  halfHeight,  halfLength,  1.0f, 0.0f,

        // Bottom face
        -halfWidth, -halfHeight, -halfLength,  0.0f, 1.0f,
         halfWidth, -halfHeight, -halfLength,  1.0f, 1.0f,
         halfWidth, -halfHeight,  halfLength,  1.0f, 0.0f,
         halfWidth, -halfHeight,  halfLength,  1.0f, 0.0f,
        -halfWidth, -halfHeight,  halfLength,  0.0f, 0.0f,
        -halfWidth, -halfHeight, -halfLength,  0.0f, 1.0f,

        // Top face
        -halfWidth,  halfHeight, -halfLength,  0.0f, 1.0f,
         halfWidth,  halfHeight, -halfLength,  1.0f, 1.0f,
         halfWidth,  halfHeight,  halfLength,  1.0f, 0.0f,
         halfWidth,  halfHeight,  halfLength,  1.0f, 0.0f,
        -halfWidth,  halfHeight,  halfLength,  0.0f, 0.0f,
        -halfWidth,  halfHeight, -halfLength,  0.0f, 1.0f
    };

    return true;
}

const std::vector<float>& Cuboid::GetVertices() const {
    return vertices;
}

 int Cuboid::GetSizeVertices() const {
    return vertices.size() * sizeof(float);
}
