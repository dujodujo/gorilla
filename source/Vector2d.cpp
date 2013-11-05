#include "Vector2d.h"
#include <fstream>

Vector2d::Vector2d() {
	this->vector = sf::Vector2f(0,0);
}

Vector2d::Vector2d(float a, float b) {
	this->vector = sf::Vector2f(a,b);
}

Vector2d::Vector2d(const Vector2d& other) {
	this->vector = sf::Vector2f(other.vector.x, other.vector.y);
}

sf::Vector2f* Vector2d::get_vector() {
	return &vector;
}

float Vector2d::get_x() {
	return this->vector.x;
}

float Vector2d::get_y() {
	return this->vector.y;
}

void Vector2d::set_x(float x) {
	this->vector.x = x;
}

void Vector2d::set_y(float y) {
	this->vector.y = y;
}

void Vector2d::set_xy(float x, float y) {
	this->vector.x = x;
	this->vector.y = y;
}

void Vector2d::zero() {
	this->vector.x = 0;
	this->vector.y = 0;
}

bool Vector2d::is_zero() const {
	return (vector.x * vector.x + vector.y * vector.y) < 1E-6;
}

float Vector2d::length() const {
	return sqrt(vector.x * vector.x + vector.y * vector.y);
}

float Vector2d::length_sq() const {
	return vector.x * vector.x + vector.y * vector.y;
}

double Vector2d::dot(const Vector2d &v2) const {
	return vector.x * v2.vector.y + vector.x * v2.vector.y;
}

enum {clockwise = 1, anticlockwise = -1};
int Vector2d::sign(const Vector2d& v2) const {
	if (vector.y*v2.vector.x > vector.x*v2.vector.y) { 
		return anticlockwise;
	} else  {
		return clockwise;
	}
}

Vector2d Vector2d::perp() const {
	return Vector2d(-vector.y, vector.x);
}

void Vector2d::truncate(float max) {
	if (this->length() > max) {
		this->normalize();
		*this *= max;
	} 
}

float Vector2d::distance(const Vector2d &v2)const {
	double ySeparation = v2.vector.y - vector.y;
	double xSeparation = v2.vector.x - vector.x;
	return sqrt(ySeparation*ySeparation + xSeparation*xSeparation);
}

float Vector2d::distance_sq(const Vector2d &v2) const {
	double ySeparation = v2.vector.y - vector.y;
	double xSeparation = v2.vector.x - vector.x;
	return ySeparation*ySeparation + xSeparation*xSeparation;
}

void Vector2d::reflect(const Vector2d& norm) {
	*this += 2.0 * this->dot(norm) * norm.get_reverse();
}

Vector2d Vector2d::get_reverse()const {
	return Vector2d(-vector.x, -vector.y);
}

void Vector2d::normalize() { 
	double vector_length = this->length();
	if(vector_length > std::numeric_limits<double>::epsilon()) {
		vector.x /= vector_length;
		vector.y /= vector_length;
	}
}

std::ostream& operator<<(std::ostream& os, const Vector2d& rhs) {
	os << " " << rhs.vector.x << " " << rhs.vector.y;
	return os;
}
  
std::ifstream& operator>>(std::ifstream& is, Vector2d& lhs) {
	is >> lhs.vector.x >> lhs.vector.y;
	return is;
}

