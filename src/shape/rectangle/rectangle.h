#pragma once

#include <vector>

class Rectangle {
public:
    Rectangle();
    ~Rectangle();

    bool Create(float width, float length);
    const std::vector<float>& GetVertices() const;
    int GetSizeVertices() const;

private:
    std::vector<float> vertices;
};
