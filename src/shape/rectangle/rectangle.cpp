#include "rectangle.h"
#include <MacTypes.h>

Rectangle::Rectangle() {
}

Rectangle::~Rectangle() {
}

bool Rectangle::Create(float width, float height) {
    float halfWidth = width / 2.0f;
    float halfHeight = height / 2.0f;

    vertices = {
        -halfWidth, -halfHeight, 0.0f,  0.0f, 0.0f,
         halfWidth, -halfHeight, 0.0f,  1.0f, 0.0f,
         halfWidth,  halfHeight, 0.0f,  1.0f, 1.0f,
         halfWidth,  halfHeight, 0.0f,  1.0f, 1.0f,
        -halfWidth,  halfHeight, 0.0f,  0.0f, 1.0f,
        -halfWidth, -halfHeight, 0.0f,  0.0f, 0.0f,
    };

    return true;
}

const std::vector<float>& Rectangle::GetVertices() const {
    return vertices;
}

 int Rectangle::GetSizeVertices() const {
    return vertices.size() * sizeof(float);
}
