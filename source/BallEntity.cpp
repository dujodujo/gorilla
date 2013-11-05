#include "BallEntity.h"
#include <cmath>
#include <iostream>

BallEntity::BallEntity(int x, int y, int mass) : 
	position(x,y),
	velocity(-1, -1),
	target(0,0),
	desired_velocity(0,0),
	steering(0,0), 
	mass(mass) {

	shape.setPosition(position);
	shape.setSize(sf::Vector2f(50, 50));
	shape.setFillColor(sf::Color(255, 255, 255));
	truncate(position, MAX_VELOCITY);
}	

BallEntity::~BallEntity() {}

void BallEntity::truncate(sf::Vector2f& vector, int max_velocity) {
	float length = this->length_vector(vector);
	float i = (float)max_velocity/ length;
	i = i < 1.0f ? 1.0f : i;
	vector.x *= i;
	vector.y *= i;
}

float BallEntity::length_vector(sf::Vector2f vector) {
	return std::sqrt(vector.x*vector.x + vector.y*vector.y);
}

void BallEntity::normalize_vector(sf::Vector2f& vector) {
	int length = length_vector(vector);
	vector.x /= length;
	vector.y /= length;
}

sf::Vector2f BallEntity::seek(sf::Vector2f& vector) {
	sf::Vector2f force;
	this->desired_velocity = subtract(vector, this->position);
	this->normalize_vector(desired_velocity);
	this->desired_velocity.x *= MAX_VELOCITY;
	this->desired_velocity.y *= MAX_VELOCITY;
	force = this->subtract(desired_velocity, this->velocity);
	return force;
}

sf::Vector2f BallEntity::subtract(sf::Vector2f& vector, sf::Vector2f& other) {
	sf::Vector2f result;
	result.x = vector.x - other.x;
	result.y = vector.y - other.y;
	return result;
}

sf::Vector2f BallEntity::add(sf::Vector2f& vector, sf::Vector2f& other) {
	sf::Vector2f result;
	result.x = vector.x + other.x;
	result.y = vector.y + other.y;
	return result;
}

void BallEntity::draw(sf::RenderTarget& canvas) {
	canvas.draw(shape);
}

void BallEntity::update(sf::Vector2i vector) {
	sf::Vector2f vec = sf::Vector2f(vector);
	target.x = vec.x;
	target.y = vec.y;

	this->steering = this->seek(target);

	truncate(steering, MAX_FORCE);
	steering.x *= (1/this->mass);
	steering.y *= (1/this->mass);

	this->velocity = this->add(velocity, steering);
	truncate(this->velocity, MAX_VELOCITY);
	this->position = this->add(position, velocity);

	this->shape.setPosition(this->position);
}