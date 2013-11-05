#ifndef TRANSFORMATIONS_H
#define TRANSFORMATIONS_H

#include <vector>
#include "Vector2d.h"
#include "Matrix2d.h"

inline void rotate_around_origin(Vector2d& v, float angle) {
	Matrix2d matrix;
	matrix.rotate(angle);
	matrix.transform_vector2d(v);
}

#endif