#pragma once

#include "engine.h"
#include "shape.h"
#include "glm/fwd.hpp"
#include "simplex.h"

class GJK {
public:
    bool colistion(const Shape& shape1, const Shape& shape2);

private:
    glm::vec3 Support(const Shape& shape1, const Shape& shape2, glm::vec3 direction);

    bool SameDirection(const glm::vec3& direction, const glm::vec3& ao);

    bool NextSimplex(Simplex& points, glm::vec3& direction);

    bool Line(Simplex& points, glm::vec3& direction);

    bool Triangle(Simplex& points, glm::vec3& direction);

    bool Tetrahedron(Simplex& points, glm::vec3& direction);

};
