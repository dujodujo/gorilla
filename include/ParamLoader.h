#ifndef PARAMLOADER_H
#define PARAM_LOADER_H
//#pragma warning(disable:4800)

#include "IniFileLoaderBase.h"

#define param (*ParamLoader::get_instance())

class ParamLoader : public IniFileLoaderBase {

private:
	ParamLoader() : IniFileLoaderBase("params.ini") {
		vehicles = this->get_next_parameter_integer();
		obstacles = this->get_next_parameter_integer();
		max_steering_force = this->get_next_parameter_float();
		max_speed = this->get_next_parameter_float();
		vehicle_mass = this->get_next_parameter_float();
		vehicle_scale = this->get_next_parameter_float();
		max_turn_rate = this->get_next_parameter_float();
		view_range = this->get_next_parameter_integer();
	}

public:
	static ParamLoader* get_instance();
	int vehicles;
	int obstacles;
	float max_steering_force;
	float max_speed;
	float vehicle_mass;
	float max_turn_rate;
	float vehicle_scale;
	int view_range;
};

#endif