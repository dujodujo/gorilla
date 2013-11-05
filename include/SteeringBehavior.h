#ifndef STEERING_BEHAVIOR_H
#define STEERING_BEHAVIOR_H

#include "BaseGameEntity.h"
#include "HeroEntity.h"
#include "Vector2d.h"
#include "Vehicle.h"
#include "Path.h"

#include <vector>

class Vehicle;

class SteeringBehavior {

private:
	Vehicle* vehicle;
	HeroEntity* target;
	Path* path;

	int view_range;

	Vector2d current_target;
	Vector2d steering_force;

public:
	SteeringBehavior(Vehicle* vehicle);
	virtual ~SteeringBehavior();
	float forward_component();
	float side_component();

	float distance_to_target();
	Vector2d start_seek(Vector2d target_position);
	Vector2d start_flee(Vector2d target_position);
	Vector2d start_pursuit(HeroEntity* evader);
	Vector2d start_arrive(Vector2d target_position);
	Vector2d start_evade(HeroEntity* follower);
	Vector2d start_follow_path();

	Vector2d calculate_group_behavior();

	Vector2d start_separation(const std::vector<Vehicle*> &neighbors);
	Vector2d start_alignment(const std::vector<Vehicle*> &neighbors);
	Vector2d start_cohesion(const std::vector<Vehicle*> &neighbors);

	void set_current_target(const Vector2d t) {current_target = t;}
	void set_target(HeroEntity* t) {target = t;}
	HeroEntity* get_target() const {return target;}

	Vector2d get_steering_force() const {return steering_force;}

	void set_path(std::list<Vector2d> npath) {path->set_path(npath);}
	Path* get_path() {return path;}
	void create_random_path(int num_waypoints, float minX, float minY, float maxX, float maxY) const;

};


#endif