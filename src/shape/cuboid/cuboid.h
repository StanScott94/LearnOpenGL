#pragma once

#include <vector>

class Cuboid {
public:
    Cuboid();
    ~Cuboid();

    bool Create(float width, float length, float height);
    const std::vector<float>& GetVertices() const;
    int GetSizeVertices() const;

private:
    std::vector<float> vertices;
    std::vector<float> indices;
};
