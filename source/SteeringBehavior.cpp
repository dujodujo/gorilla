#include "SteeringBehavior.h"
#include "BaseGameEntity.h"
#include "ParamLoader.h"
#include "Vector2d.h"
#include "Map.h"
#include <iostream>

SteeringBehavior::SteeringBehavior(Vehicle* vehicle) :
	vehicle(vehicle),
	target(NULL),
	path(NULL),
	view_range(param.view_range) {
	
	path = new Path(4, 50, 50, 450, 450, true);
	path->loop_on();
}

SteeringBehavior::~SteeringBehavior() {
	delete path;
}

float SteeringBehavior::forward_component() {
	return vehicle->get_heading().dot(steering_force);
}

float SteeringBehavior::side_component() {
	return vehicle->get_side().dot(steering_force);
}

float SteeringBehavior::distance_to_target() {
	Vector2d distance = target->get_position() - vehicle->get_position();
	return distance.length();
}

Vector2d SteeringBehavior::start_seek(Vector2d target_position) {
	Vector2d desired_velocity = 
		vec2d_normalize(target_position - vehicle->get_position()) * vehicle->get_max_speed();
	return desired_velocity - vehicle->get_velocity();
}

Vector2d SteeringBehavior::start_arrive(Vector2d target_position) {
	Vector2d target = target_position - vehicle->get_position();
	float distance = target.length();
	if(distance > 0) {
		float speed = distance / 0.5f;
		speed = std::min(speed, vehicle->get_max_speed());
		Vector2d desired_velocity = target * speed/distance;
		return desired_velocity - vehicle->get_velocity();
	}
	return Vector2d(0.0f, 0.0f);
}

Vector2d SteeringBehavior::start_flee(Vector2d target_position) {
	Vector2d desired_velocity = 
		vec2d_normalize(vehicle->get_position() - target_position) * vehicle->get_max_speed();
	return (desired_velocity - vehicle->get_velocity());
}

Vector2d SteeringBehavior::start_pursuit(HeroEntity* evader) {
	Vector2d evader_position = evader->get_position() - vehicle->get_position();
	float relative_heading = vehicle->get_heading().dot(evader->get_heading());
	if(evader_position.dot(vehicle->get_heading()) > 0 && (relative_heading < -0.95f)) {
		return start_seek(evader->get_position());
	}
	float look_forward = evader_position.length() / (vehicle->get_max_speed() + evader->get_speed());
	Vector2d position = evader->get_position() + evader->get_velocity() * look_forward;
	return start_seek(position);
}

Vector2d SteeringBehavior::start_evade(HeroEntity* follower) {
	Vector2d follower_position = follower->get_position()-vehicle->get_position();
	float look_ahead = follower_position.length() / (vehicle->get_max_speed() + follower->get_speed());
	return start_flee(follower->get_position() + follower->get_velocity() * look_ahead);
}

void SteeringBehavior::create_random_path(int num_waypoints, float minX, float minY, float maxX, float maxY) const {
	this->path->create_random_path(num_waypoints, minX, minY, maxX, maxY);
}

Vector2d SteeringBehavior::calculate_group_behavior() {
	Vector2d force;
	vehicle->get_map()->tag_vehicles_in_range(vehicle, view_range);
	//force += start_separation(vehicle->get_map()->get_vehicles());
	//force += start_alignment(vehicle->get_map()->get_vehicles());
	force += start_cohesion(vehicle->get_map()->get_vehicles());
	return force;
}

Vector2d SteeringBehavior::start_separation(const std::vector<Vehicle*> &neighbors) {
	Vector2d separation_force;
	for(int i=0; i < neighbors.size(); i++) {
		if(neighbors[i] != vehicle && neighbors[i]->is_tag()) {
			Vector2d to_target = vehicle->get_position() - neighbors[i]->get_position();
			separation_force += vec2d_normalize(to_target)/to_target.length();
		}
	}
	return separation_force;
}

Vector2d SteeringBehavior::start_alignment(const std::vector<Vehicle*> &neighbors) {
	Vector2d average_heading;
	int neighbors_count = 0;
	for(int i=0; i < neighbors.size(); i++) {
		if(neighbors[i] != vehicle && neighbors[i]->is_tag()) {
			average_heading += neighbors[i]->get_heading();
			neighbors_count++;
		}
	}
	if(neighbors_count > 0) {
		average_heading /= (float)neighbors_count;
		average_heading -= vehicle->get_heading();
	}
	return average_heading;
}

Vector2d SteeringBehavior::start_cohesion(const std::vector<Vehicle*> &neighbors) {
	Vector2d center, steering_force;
	int neighbors_count = 0;
	for(int i=0; i < neighbors.size(); i++) {
		if(neighbors[i] != vehicle && neighbors[i]->is_tag()) {
			center += neighbors[i]->get_position();
		}
	}
	if(neighbors_count > 0) {
		center /= (float)neighbors_count;
		start_seek(center);
	}
	return vec2d_normalize(steering_force);
}

Vector2d SteeringBehavior::start_follow_path() {
	float current_distance = vec2d_distance(path->get_current_waypoint(), vehicle->get_position());
	float waypoint_seek_distance = 5;
	if(current_distance < waypoint_seek_distance) {
		path->set_next_waypoint();
	}
	float decelleration_radius = 10;
	if(current_distance < decelleration_radius) {
		return start_arrive(path->get_current_waypoint());
	} else {
		return start_seek(path->get_current_waypoint());
	}
}