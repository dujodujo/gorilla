#ifndef MOVING_ENTITY_H
#define MOVING_ENTITY_H

#include <iostream>
#include <cassert>
#include "BaseGameEntity.h"
#include "Vector2d.h"
#include <SFML\System\Vector2.hpp>

class MovingEntity : public BaseGameEntity {

protected:
	Vector2d velocity;
	Vector2d heading;
	Vector2d side;

	float mass;
	float max_speed;
	float max_force;
	float max_turn_rate;

public:
	MovingEntity(Vector2d position,
				float radius,
				Vector2d velocity,
				float max_speed,
				Vector2d heading,
				float mass,
				Vector2d scale,
				float max_force,
				float turn_rate) : 
				BaseGameEntity(position, Vector2d(1.0f, 1.0f), radius),
				heading(heading),
				velocity(velocity),
				mass(mass),
				side(heading.perp()),
				max_speed(max_speed),
				max_turn_rate(turn_rate),
				max_force(max_force) {
	this->scale = scale;
}

	virtual ~MovingEntity() {}
	Vector2d get_velocity() const {return this->velocity;}
	virtual void set_velocity(Vector2d& vector) {this->velocity = vector;}
	float get_mass() const {return this->mass;}
	Vector2d get_side() {return this->side;}
	Vector2d get_heading() const {return this->heading;}
	float get_speed() const {return this->velocity.length();}
	float get_speed_sq() const {return this->velocity.length_sq();}
	void set_heading(Vector2d heading);

	float get_max_speed() const {return this->max_speed;}
	void set_max_speed(float speed) {this->max_speed = speed;}
	float get_max_force() const {return this->max_force;}
	void set_max_force(float force) {this->max_force = force;}
	bool is_max_speed() const {return max_speed * max_speed > this->velocity.length_sq();}
	float get_max_turn_rate() const {return this->max_turn_rate;}
	void set_max_turn_rate(float val) {this->max_turn_rate = val;}

};
	
#endif