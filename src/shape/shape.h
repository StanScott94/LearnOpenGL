#pragma once

#include "engine.h"
#include <string>
#include <vector>

class Shape {
public:
    Shape(std::string id, float width, float length, float height);
    ~Shape();

    const std::vector<float>& GetVertices() const;
    int GetSizeVertices() const;
    std::string GetId() const;
    glm::vec3 FindFurthestPoint(glm::vec3 direction) const;
    void UpdateVertices(const glm::mat4& modelMatrix);

private:
    std::vector<float> initialVertices;
    std::vector<float> vertices;
    std::string id;
};
