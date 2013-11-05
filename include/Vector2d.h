#ifndef VECTOR2D_H
#define VECTOR2D_H

#include <SFML\System\Vector2.hpp>
#include <math.h>
#include <iosfwd>
#include <limits>

class Vector2d {

public:
	sf::Vector2f vector;
	sf::Vector2f* get_vector();

public:
	Vector2d();
	Vector2d(float a, float b);
	Vector2d(const Vector2d &other);

	float get_x();
	float get_y();
	void set_x(float x);
	void set_y(float y);
	void set_xy(float x, float y);
	void zero();
	bool is_zero() const;
	float length() const;
	float length_sq() const;
	void normalize();
	double dot(const Vector2d& v2) const;
	int sign(const Vector2d& v2) const;
	Vector2d perp() const;
	void truncate(float max);
	float distance(const Vector2d &v2) const;
	float distance_sq(const Vector2d &v2) const;
	void reflect(const Vector2d& norm);
	Vector2d get_reverse() const;

	const Vector2d& operator+=(const Vector2d &rhs) {
		vector.x += rhs.vector.x;
		vector.y += rhs.vector.y;
		return *this;
	}

	const Vector2d& operator-=(const Vector2d &rhs) {
		vector.x -= rhs.vector.x;
		vector.y -= rhs.vector.y;
		return *this;
	}

	const Vector2d& operator*=(const float& rhs) {
		vector.x *= rhs;
		vector.y *= rhs;
		return *this;
	}

	const Vector2d& operator/=(const float& rhs) {
		vector.x /= rhs;
		vector.y /= rhs;
		return *this;
	}

	bool operator==(const Vector2d& rhs) const {
		return vector.x==rhs.vector.x && vector.y==rhs.vector.y;
	}

	bool operator!=(const Vector2d& rhs) const {
		return vector.x!=rhs.vector.x || vector.y!=rhs.vector.y;
	}
	
};

inline Vector2d operator*(const Vector2d &lhs, float rhs);
inline Vector2d operator*(float lhs, const Vector2d &rhs);
inline Vector2d operator-(const Vector2d &lhs, const Vector2d &rhs);
inline Vector2d operator/(const Vector2d &lhs, float val);
inline Vector2d operator+(const Vector2d &lhs, const Vector2d &rhs);
std::ostream& operator<<(std::ostream& os, const Vector2d& rhs);
std::ifstream& operator>>(std::ifstream& is, Vector2d& lhs);

inline Vector2d operator+(const Vector2d &lhs, const Vector2d &rhs) {
	Vector2d result(lhs);
	result.vector.x -= rhs.vector.x;
	result.vector.y -= rhs.vector.y;
	return result;
}

inline Vector2d vec2d_normalize(const Vector2d &v) {
	Vector2d vec = v;
	float vector_length = vec.length();
	if (vector_length > std::numeric_limits<float>::epsilon()) {
		vec.vector.x /= vector_length;
		vec.vector.y /= vector_length;
	}
	return vec;
}

inline float vec2d_distance(const Vector2d &v1, const Vector2d &v2) {
	float ySeparation = v2.vector.y - v1.vector.y;
	float xSeparation = v2.vector.x - v1.vector.x;
	return sqrt(ySeparation*ySeparation + xSeparation*xSeparation);
}

inline float vec2d_distance_sq(const Vector2d &v1, const Vector2d &v2) {
	float ySeparation = v2.vector.y - v1.vector.y;
	float xSeparation = v2.vector.x - v1.vector.x;
	return ySeparation*ySeparation + xSeparation*xSeparation;
}

inline double vec2d_length(const Vector2d& v) {
	return sqrt(v.vector.x*v.vector.x + v.vector.y*v.vector.y);
}

inline double vec2d_length_sq(const Vector2d& v) {
	return (v.vector.x*v.vector.x + v.vector.y*v.vector.y);
}

inline Vector2d operator*(const Vector2d &lhs, float rhs) {
	Vector2d result(lhs);
	result *= rhs;
	return result;
}

inline Vector2d operator*(float lhs, const Vector2d &rhs) {
	Vector2d result(rhs);
	result *= lhs;
	return result;
}

inline Vector2d operator-(const Vector2d &lhs, const Vector2d &rhs) {
	Vector2d result(lhs);
	result.vector.x -= rhs.vector.x;
	result.vector.y -= rhs.vector.y;
	return result;
}

inline Vector2d operator/(const Vector2d &lhs, float val) {
	Vector2d result(lhs);
	result.vector.x /= val;
	result.vector.y /= val;
	return result;
}

#endif