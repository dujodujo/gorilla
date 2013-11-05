#include "SteeringBehavior.h"
#include "VehicleStates.h"

StartFollowPath* StartFollowPath::get_instance() {
	static StartFollowPath instance;
	return &instance;
}

void StartFollowPath::start(Vehicle* vehicle) {
	Vector2d steering_force = vehicle->get_steering()->get_steering_force();
	steering_force.zero();
	steering_force += vehicle->get_steering()->start_follow_path();
	steering_force.truncate(vehicle->get_max_force());

	vehicle->set_velocity(steering_force);
	vehicle->set_position();
	//std::cout << vehicle->get_velocity()<< "\n";

	if(vehicle->get_steering()->distance_to_target() < 150) {
		vehicle->get_state_machine()->change_state(StartPursuit::get_instance());
	}
}

void StartFollowPath::stop(Vehicle* vehicle) {}

StartPursuit* StartPursuit::get_instance() {
	static StartPursuit instance;
	return &instance;
}

void StartPursuit::start(Vehicle* vehicle) {
	Vector2d steering_force = vehicle->get_steering()->get_steering_force();
	steering_force.zero();
	steering_force += vehicle->get_steering()->start_pursuit(vehicle->get_steering()->get_target());
	steering_force += vehicle->get_steering()->calculate_group_behavior();
	steering_force.truncate(vehicle->get_max_force());

	vehicle->set_velocity(steering_force);
	vehicle->set_position();

	if(vehicle->get_steering()->distance_to_target() > 150) {
		vehicle->get_state_machine()->change_state(StartFollowPath::get_instance());
	}
}

void StartPursuit::stop(Vehicle* vehicle) {}