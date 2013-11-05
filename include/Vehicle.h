#ifndef VEHICLE_H
#define VEHICLE_H

#include <SFML\Graphics\CircleShape.hpp>
#include "SteeringBehavior.h"
#include "VehicleStates.h"
#include "StateMachine.h"
#include "MovingEntity.h"
#include "Vector2d.h"
#include <vector>
#include <list>
#include <cstdlib>

class SteeringBehavior;
class Map;

class Vehicle : public MovingEntity {

private:
	SteeringBehavior* steering;
	StateMachine<Vehicle>* state_machine;
	Map* map;
	sf::CircleShape shape;
	int threat;
	float time_now;

public:
	Vehicle(Map* map,
			Vector2d position,
			float rotation,
			Vector2d velocity,
			float mass,
			float max_force,
			float max_speed,
			float max_turn_rate,
			float scale);

	Vehicle(const Vehicle&);
	Vehicle& operator=(const Vehicle&);
	~Vehicle();

	float get_time() {return time_now;}

	void set_threat(int threat) {this->threat = threat;}
	int get_threat() {return threat;}

	void set_velocity(Vector2d steering_force);
	void set_position();

	SteeringBehavior* get_steering() const;
	StateMachine<Vehicle>* get_state_machine() const {return state_machine;}
	Map* get_map() const {return map;}

	void update(float delta_time);
	void draw(sf::RenderTarget& canvas);

};

#endif