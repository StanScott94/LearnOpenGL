#include "gjk.h"

bool GJK::colistion(const Shape& shape1, const Shape& shape2) {
    glm::vec3 support = Support(shape1, shape2, glm::vec3(1, 0, 0));

    Simplex points;
    points.push_front(support);

    glm::vec3 direction = -support;

    while (true) {
	support = Support(shape1, shape2, direction);

	if (dot(support, direction) < 0) {
	    return false;
	}

	points.push_front(support);

	if (NextSimplex(points, direction)) {
	    return true;
	}
    }
};

glm::vec3 GJK::Support(const Shape& shape1, const Shape& shape2, glm::vec3 direction) {
    return shape1.FindFurthestPoint(direction) - shape2.FindFurthestPoint(-direction);
}

bool GJK::SameDirection(const glm::vec3& direction, const glm::vec3& ao) {
    return dot(direction, ao) > 0;
}

bool GJK::NextSimplex(Simplex& points, glm::vec3& direction) {
    switch (points.getSize()) {
	case 2: return Line(points, direction);
	case 3: return Triangle(points, direction);
	case 4: return Tetrahedron(points, direction);
    }

    return false;
}

bool GJK::Line(Simplex& points, glm::vec3& direction) {
    glm::vec3 a = points[0];
    glm::vec3 b = points[1];

    glm::vec3 ab = b - a;
    glm::vec3 ao = -a;

    if (SameDirection(ab, ao)) {
	direction = cross(cross(ab, ao), ab);
    } else {
        points = { a };
        direction = ao;
    }

    return false;
}

bool GJK::Triangle(Simplex& points, glm::vec3& direction) {
    glm::vec3 a = points[0];
    glm::vec3 b = points[1];
    glm::vec3 c = points[2];

    glm::vec3 ab = b - a;
    glm::vec3 ac = c - a;
    glm::vec3 ao = -a;
 
    glm::vec3 abc = cross(ab, ac);

    if (SameDirection(cross(abc, ac), ao)) {
	if (SameDirection(ac, ao)) {
	    points = { a, c };
	    direction = cross(cross(ac, ao), ac);
	} else {
	    return Line(points = { a, b }, direction);
	}
    } else {
	if (SameDirection(cross(ab, abc), ao)) {
	    return Line(points = { a, b }, direction);
	} else {
	    if (SameDirection(abc, ao)) {
		direction = abc;
	    } else {
		points = { a, c, b };
		direction = -abc;
	    }
	}
    }

    return false;
}

bool GJK::Tetrahedron(Simplex& points, glm::vec3& direction) {
    glm::vec3 a = points[0];
    glm::vec3 b = points[1];
    glm::vec3 c = points[2];
    glm::vec3 d = points[3];

    glm::vec3 ab = b - a;
    glm::vec3 ac = c - a;
    glm::vec3 ad = d - a;
    glm::vec3 ao =   - a;

    glm::vec3 abc = cross(ab, ac);
    glm::vec3 acd = cross(ac, ad);
    glm::vec3 adb = cross(ad, ab);

    if (SameDirection(abc, ao)) {
        return Triangle(points = { a, b, c }, direction);
    }
    if (SameDirection(acd, ao)) {
        return Triangle(points = { a, c, d }, direction);
    }
    if (SameDirection(adb, ao)) {
        return Triangle(points = { a, d, b }, direction);
    }

    return true;
}

