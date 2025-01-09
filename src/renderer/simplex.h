#pragma once

#include "engine.h"
#include <array>

struct Simplex {
public:
    Simplex(): size(0) {
    }

    Simplex& operator=(std::initializer_list<glm::vec3> list) {
        size = 0;
        for (glm::vec3 point : list) {
            points[size++] = point;
	}
        return *this;
    }

    void push_front(glm::vec3 point) {
        points = { point, points[0], points[1], points[2] };
	size = std::min(size + 1, 4);
    }

    glm::vec3& operator[](int i) {
        return points[i];
    }

    size_t getSize() const {
        return size;
    }

    auto begin() const {
        return points.begin();
    }

    auto end() const {
        return points.end() - (4 - size);
    }

private:
    std::array<glm::vec3, 4> points;
    int size;
};
