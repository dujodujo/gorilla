#include "VehicleStates.h"
#include "Vehicle.h"

#include <vector>
#include <list>
#include <cmath>
#include <math.h>

Vehicle::Vehicle(Map* map,
				Vector2d position,
				float rotation,
				Vector2d velocity,
				float mass,
				float max_force,
				float max_speed,
				float max_turn_rate,
				float scale) : 
				MovingEntity(position, 
				scale, 
				velocity,
				max_speed,
				Vector2d(std::sin(scale), -std::cos(scale)),
				mass,
				Vector2d(scale, scale),
				max_force,
				max_turn_rate),
				map(map) {

	shape.setPosition(sf::Vector2f(position.get_x(), position.get_y()));
	shape.setRadius(5.0f);
	shape.setFillColor(sf::Color(255, 255*std::rand(), 255*std::rand()));
	steering = new SteeringBehavior(this);
	state_machine = new StateMachine<Vehicle>(this);
	state_machine->set_current_state(StartPursuit::get_instance());
}

Vehicle::~Vehicle() {
	delete steering;
	delete state_machine;
}

void Vehicle::set_velocity(Vector2d steering_force) {
	Vector2d accelaration = steering_force / mass;
	std::cout << accelaration << "\n";
	this->velocity = accelaration * time_now;
	this->velocity.truncate(this->max_speed);

	if(velocity.length_sq() > 0.00000001) {
		this->heading = vec2d_normalize(velocity);
		this->side = heading.perp();
	}
}

void Vehicle::set_position() {
	this->position += this->velocity * time_now;
	shape.setPosition(sf::Vector2f(position.get_x(), position.get_y()));
	shape.setFillColor(sf::Color(255, 125, 125));
}

SteeringBehavior* Vehicle::get_steering() const {
	return steering;
}

void Vehicle::update(float delta_time) {
	this->time_now = delta_time;
	state_machine->update();
}

void Vehicle::draw(sf::RenderTarget& canvas) {
	canvas.draw(shape);
	this->steering->get_path()->draw(canvas);
}