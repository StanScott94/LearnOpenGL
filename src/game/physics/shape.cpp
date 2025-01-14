#include "shape.h"
#include <string>

Shape::Shape(float width, float length, float height) {
    float halfWidth = width / 2.0f;
    float halfLength = length / 2.0f;
    float halfHeight = height / 2.0f;

    initialVertices = vertices = {
        // Front face
        -halfWidth, -halfHeight, -halfLength, 0.0f, 0.0f, -1.0f,
         halfWidth, -halfHeight, -halfLength, 0.0f, 0.0f, -1.0f,
         halfWidth,  halfHeight, -halfLength, 0.0f, 0.0f, -1.0f,
         halfWidth,  halfHeight, -halfLength, 0.0f, 0.0f, -1.0f,
        -halfWidth,  halfHeight, -halfLength, 0.0f, 0.0f, -1.0f,
        -halfWidth, -halfHeight, -halfLength, 0.0f, 0.0f, -1.0f,

        // Back face
        -halfWidth, -halfHeight,  halfLength, 0.0f, 0.0f, 1.0f,
         halfWidth, -halfHeight,  halfLength, 0.0f, 0.0f, 1.0f,
         halfWidth,  halfHeight,  halfLength, 0.0f, 0.0f, 1.0f,
         halfWidth,  halfHeight,  halfLength, 0.0f, 0.0f, 1.0f,
        -halfWidth,  halfHeight,  halfLength, 0.0f, 0.0f, 1.0f,
        -halfWidth, -halfHeight,  halfLength, 0.0f, 0.0f, 1.0f,

        // Left face
        -halfWidth,  halfHeight,  halfLength, -1.0f, 0.0f, 0.0f,
        -halfWidth,  halfHeight, -halfLength, -1.0f, 0.0f, 0.0f,
        -halfWidth, -halfHeight, -halfLength, -1.0f, 0.0f, 0.0f,
        -halfWidth, -halfHeight, -halfLength, -1.0f, 0.0f, 0.0f,
        -halfWidth, -halfHeight,  halfLength, -1.0f, 0.0f, 0.0f,
        -halfWidth,  halfHeight,  halfLength, -1.0f, 0.0f, 0.0f,

        // Right face
         halfWidth,  halfHeight,  halfLength, 1.0f, 0.0f, 0.0f,
         halfWidth,  halfHeight, -halfLength, 1.0f, 0.0f, 0.0f,
         halfWidth, -halfHeight, -halfLength, 1.0f, 0.0f, 0.0f,
         halfWidth, -halfHeight, -halfLength, 1.0f, 0.0f, 0.0f,
         halfWidth, -halfHeight,  halfLength, 1.0f, 0.0f, 0.0f,
         halfWidth,  halfHeight,  halfLength, 1.0f, 0.0f, 0.0f,

        // Bottom face
        -halfWidth, -halfHeight, -halfLength, 0.0f, -1.0f, 0.0f,
         halfWidth, -halfHeight, -halfLength, 0.0f, -1.0f, 0.0f,
         halfWidth, -halfHeight,  halfLength, 0.0f, -1.0f, 0.0f,
         halfWidth, -halfHeight,  halfLength, 0.0f, -1.0f, 0.0f,
        -halfWidth, -halfHeight,  halfLength, 0.0f, -1.0f, 0.0f,
        -halfWidth, -halfHeight, -halfLength, 0.0f, -1.0f, 0.0f,

        // Top face
        -halfWidth,  halfHeight, -halfLength, 0.0f, 1.0f, 0.0f,
         halfWidth,  halfHeight, -halfLength, 0.0f, 1.0f, 0.0f,
         halfWidth,  halfHeight,  halfLength, 0.0f, 1.0f, 0.0f,
         halfWidth,  halfHeight,  halfLength, 0.0f, 1.0f, 0.0f,
        -halfWidth,  halfHeight,  halfLength, 0.0f, 1.0f, 0.0f,
        -halfWidth,  halfHeight, -halfLength, 0.0f, 1.0f, 0.0f,
    };

    // cube vetices
    std::vector<float> unusedVertices = {
        // Front face
        -halfWidth, -halfHeight, -halfLength,
         halfWidth, -halfHeight, -halfLength,
         halfWidth,  halfHeight, -halfLength,
         halfWidth,  halfHeight, -halfLength,
        -halfWidth,  halfHeight, -halfLength,
        -halfWidth, -halfHeight, -halfLength,

        // Back face
        -halfWidth, -halfHeight,  halfLength,
         halfWidth, -halfHeight,  halfLength,
         halfWidth,  halfHeight,  halfLength,
         halfWidth,  halfHeight,  halfLength,
        -halfWidth,  halfHeight,  halfLength,
        -halfWidth, -halfHeight,  halfLength,

        // Left face
        -halfWidth,  halfHeight,  halfLength,
        -halfWidth,  halfHeight, -halfLength,
        -halfWidth, -halfHeight, -halfLength,
        -halfWidth, -halfHeight, -halfLength,
        -halfWidth, -halfHeight,  halfLength,
        -halfWidth,  halfHeight,  halfLength,

        // Right face
         halfWidth,  halfHeight,  halfLength,
         halfWidth,  halfHeight, -halfLength,
         halfWidth, -halfHeight, -halfLength,
         halfWidth, -halfHeight, -halfLength,
         halfWidth, -halfHeight,  halfLength,
         halfWidth,  halfHeight,  halfLength,

        // Bottom face
        -halfWidth, -halfHeight, -halfLength,
         halfWidth, -halfHeight, -halfLength,
         halfWidth, -halfHeight,  halfLength,
         halfWidth, -halfHeight,  halfLength,
        -halfWidth, -halfHeight,  halfLength,
        -halfWidth, -halfHeight, -halfLength,

        // Top face
        -halfWidth,  halfHeight, -halfLength,
         halfWidth,  halfHeight, -halfLength,
         halfWidth,  halfHeight,  halfLength,
         halfWidth,  halfHeight,  halfLength,
        -halfWidth,  halfHeight,  halfLength,
        -halfWidth,  halfHeight, -halfLength,
    };

    // cube vetices with texture
    std::vector<float> unusedVerticesWithTextureCoordinates = {
        // Front face
        -halfWidth, -halfHeight, -halfLength, 0.0f, 0.0f,
         halfWidth, -halfHeight, -halfLength, 1.0f, 0.0f,
         halfWidth,  halfHeight, -halfLength, 1.0f, 1.0f,
         halfWidth,  halfHeight, -halfLength, 1.0f, 1.0f,
        -halfWidth,  halfHeight, -halfLength, 0.0f, 1.0f,
        -halfWidth, -halfHeight, -halfLength, 0.0f, 0.0f,

        // Back face
        -halfWidth, -halfHeight,  halfLength, 0.0f, 0.0f,
         halfWidth, -halfHeight,  halfLength, 1.0f, 0.0f,
         halfWidth,  halfHeight,  halfLength, 1.0f, 1.0f,
         halfWidth,  halfHeight,  halfLength, 1.0f, 1.0f,
        -halfWidth,  halfHeight,  halfLength, 0.0f, 1.0f,
        -halfWidth, -halfHeight,  halfLength, 0.0f, 0.0f,

        // Left face
        -halfWidth,  halfHeight,  halfLength, 1.0f, 0.0f,
        -halfWidth,  halfHeight, -halfLength, 1.0f, 1.0f,
        -halfWidth, -halfHeight, -halfLength, 0.0f, 1.0f,
        -halfWidth, -halfHeight, -halfLength, 0.0f, 1.0f,
        -halfWidth, -halfHeight,  halfLength, 0.0f, 0.0f,
        -halfWidth,  halfHeight,  halfLength, 1.0f, 0.0f,

        // Right face
         halfWidth,  halfHeight,  halfLength, 1.0f, 0.0f,
         halfWidth,  halfHeight, -halfLength, 1.0f, 1.0f,
         halfWidth, -halfHeight, -halfLength, 0.0f, 1.0f,
         halfWidth, -halfHeight, -halfLength, 0.0f, 1.0f,
         halfWidth, -halfHeight,  halfLength, 0.0f, 0.0f,
         halfWidth,  halfHeight,  halfLength, 1.0f, 0.0f,

        // Bottom face
        -halfWidth, -halfHeight, -halfLength, 0.0f, 1.0f,
         halfWidth, -halfHeight, -halfLength, 1.0f, 1.0f,
         halfWidth, -halfHeight,  halfLength, 1.0f, 0.0f,
         halfWidth, -halfHeight,  halfLength, 1.0f, 0.0f,
        -halfWidth, -halfHeight,  halfLength, 0.0f, 0.0f,
        -halfWidth, -halfHeight, -halfLength, 0.0f, 1.0f,

        // Top face
        -halfWidth,  halfHeight, -halfLength, 0.0f, 1.0f,
         halfWidth,  halfHeight, -halfLength, 1.0f, 1.0f,
         halfWidth,  halfHeight,  halfLength, 1.0f, 0.0f,
         halfWidth,  halfHeight,  halfLength, 1.0f, 0.0f,
        -halfWidth,  halfHeight,  halfLength, 0.0f, 0.0f,
        -halfWidth,  halfHeight, -halfLength, 0.0f, 1.0f
    };
}

Shape::~Shape() {
}

const std::vector<float>& Shape::GetVertices() const {
    return vertices;
}

int Shape::GetSizeVertices() const {
    return vertices.size() * sizeof(float);
}

glm::vec3 Shape::FindFurthestPoint(glm::vec3 direction) const {
    glm::vec3  maxPoint;
    float maxDistance = -FLT_MAX;

    for (size_t i = 0; i < vertices.size(); i += 6) {
        glm::vec3 vertex = glm::vec3(vertices[i], vertices[i + 1], vertices[i + 2]);
        float distance = glm::dot(vertex, direction);
        if (distance > maxDistance) {
            maxDistance = distance;
            maxPoint = vertex;
        }
    }

    return maxPoint;
}

void Shape::UpdateVertices(const glm::mat4& modelMatrix) {
    for (size_t i = 0; i < initialVertices.size(); i += 6) {
        glm::vec4 vertexPosition = glm::vec4(initialVertices[i], initialVertices[i + 1], initialVertices[i + 2], 1.0f);
        glm::vec4 transformedPosition = modelMatrix * vertexPosition;

        vertices[i]     = transformedPosition.x;
        vertices[i + 1] = transformedPosition.y;
        vertices[i + 2] = transformedPosition.z;
    }
}
