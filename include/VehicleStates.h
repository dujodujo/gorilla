#ifndef VEHICLE_STATES_H
#define VEHICLE_STATES_H

#include "State.h"
class Vehicle;

class StartFollowPath : public State<Vehicle> {

public:
	StartFollowPath() : State<Vehicle>() {}

	static StartFollowPath* get_instance();
	virtual void start(Vehicle* vehicle);
	virtual void stop(Vehicle* vehicle);
};

class StartPursuit : public State<Vehicle> {

public:
	StartPursuit() : State<Vehicle>() {}

	static StartPursuit* get_instance();
	virtual void start(Vehicle* vehicle);
	virtual void stop(Vehicle* vehicle);
};

#endif