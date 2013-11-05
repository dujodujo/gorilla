#ifndef MATRIX2D_H
#define MATRIX2D_H

#include <math.h>
#include <vector>
#include "Vector2d.h"
#include <iostream>

class Matrix2d {

private:
	struct Matrix {
		float x11, x12, x13;
		float x21, x22, x23;
		float x31, x32, x33;

		Matrix() {
			x11=0.0f; x12=0.0f; x13=0.0f;
			x21=0.0f; x22=0.0f; x23=0.0f;
			x31=0.0f; x32=0.0f; x33=0.0f;
		}
	};

	Matrix matrix;
	inline void matrix_multiply(Matrix &matrix);

public:
	Matrix2d() {
		identity();
	}
	
	inline void identity();
	inline void translate(float x, float y);
	inline void scale(float x, float y);
	inline void rotate(float rotation);
	inline void rotate(const Vector2d& fwd, const Vector2d &side);
	inline void transform_vector2d(std::vector<Vector2d> &points);
	inline void transform_vector2d(Vector2d &point);

	void set_x11(float val) {matrix.x11=val;}
	void set_x12(float val) {matrix.x12=val;}
	void set_x13(float val) {matrix.x13=val;}

	void set_x21(float val) {matrix.x21=val;}
	void set_x22(float val) {matrix.x22=val;}
	void set_x23(float val) {matrix.x23=val;}

	void set_x31(float val) {matrix.x31=val;}
	void set_x32(float val) {matrix.x32=val;}
	void set_x33(float val) {matrix.x33=val;}
};

inline void Matrix2d::matrix_multiply(Matrix& mat) {
	Matrix2d::Matrix matrix_temp;

	//first row
	matrix_temp.x11 = (matrix.x11 * mat.x11) + (matrix.x12 * mat.x21) + (matrix.x13 * mat.x31);
	matrix_temp.x12 = (matrix.x11 * mat.x12) + (matrix.x12 * mat.x22) + (matrix.x13 * mat.x32);
	matrix_temp.x13 = (matrix.x11 * mat.x13) + (matrix.x12 * mat.x23) + (matrix.x13 * mat.x33);
	//second row
	matrix_temp.x21 = (matrix.x21 * mat.x11) + (matrix.x22 * mat.x21) + (matrix.x23 * mat.x31);
	matrix_temp.x22 = (matrix.x21 * mat.x12) + (matrix.x22 * mat.x22) + (matrix.x23 * mat.x32);
	matrix_temp.x23 = (matrix.x21 * mat.x13) + (matrix.x22 * mat.x23) + (matrix.x23 * mat.x33);
	//third row
	matrix_temp.x31 = (matrix.x31 * mat.x11) + (matrix.x32 * mat.x21) + (matrix.x33 * mat.x31);
	matrix_temp.x32 = (matrix.x31 * mat.x12) + (matrix.x32 * mat.x22) + (matrix.x33 * mat.x32);
	matrix_temp.x33 = (matrix.x31 * mat.x13) + (matrix.x32 * mat.x23) + (matrix.x33 * mat.x33);
	
	matrix = matrix_temp;
}

inline void Matrix2d::transform_vector2d(std::vector<Vector2d> &points) {
	for(int i = 0; i < points.size(); i++) {
		float temp_x = (matrix.x11*points[i].get_x()) + (matrix.x21*points[i].get_y()) + (matrix.x31);
		float temp_y = (matrix.x12*points[i].get_x()) + (matrix.x22*points[i].get_y()) + (matrix.x32);
		points[i].vector.x = temp_x;
		points[i].vector.y = temp_y;
	}
}

inline void Matrix2d::transform_vector2d(Vector2d &point) {
	float temp_x = (matrix.x11*point.vector.x) + (matrix.x21*point.vector.y) + (matrix.x31);
	float temp_y = (matrix.x12*point.vector.x) + (matrix.x22*point.vector.y) + (matrix.x32);
	point.vector.x = temp_x;
	point.vector.y = temp_y;
}

inline void Matrix2d::identity() {
	matrix.x11=1; matrix.x12=0; matrix.x13=0;
	matrix.x21=0; matrix.x22=1; matrix.x23=0;
	matrix.x31=0; matrix.x32=0; matrix.x33=1;
}

inline void Matrix2d::translate(float x, float y) {
	Matrix m;
	m.x11=1; m.x12=0; m.x13=0;
	m.x21=0; m.x22=1; m.x23=0;
	m.x31=x; m.x32=y; m.x33=1;
	this->matrix_multiply(m);
}

inline void Matrix2d::scale(float x, float y) {
	Matrix2d::Matrix m;
	m.x11=x; m.x12=0; m.x13=0;
	m.x21=0; m.x22=y; m.x23=0;
	m.x31=0; m.x32=0; m.x33=1;
	this->matrix_multiply(m);
}

inline void Matrix2d::rotate(float rotation) {
	Matrix2d::Matrix m;
	float sin = (float)std::sin(rotation);
	float cos = (float)std::cos(rotation);
	m.x11=cos; m.x12=sin; m.x13=0;
	m.x21=-sin; m.x22=cos; m.x23=0;
	m.x31=0; m.x32=0; m.x33=1;
	this->matrix_multiply(m);
}

inline void Matrix2d::rotate(const Vector2d& fwd, const Vector2d &side) {
	Matrix2d::Matrix m;
	m.x11=fwd.vector.x; m.x12=fwd.vector.y; m.x13=0;
	m.x21=side.vector.x; m.x22=side.vector.y; m.x23=0;
	m.x31=0; m.x32=0; m.x33=1;
	this->matrix_multiply(m);
}

#endif