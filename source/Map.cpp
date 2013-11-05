#include "ParamLoader.h"
#include "Map.h"


Map::Map() :
	hero(NULL) {
	hero = new HeroEntity(Vector2d(475.0f, 475.0f),		//start position.
						0,								//start rotation
						Vector2d(0.0f,0.0f),			//velocity
						param.vehicle_mass,				//mass
						param.max_steering_force,		//force
						param.max_speed,				//max velocity
						param.max_turn_rate,			//turn rate
						param.vehicle_scale);			//scale

	//setup vehicles.
	int j = 0;
	for(int i = 0; i < param.vehicles; i++) {
		j += 50; 
		Vector2d rand_position = Vector2d(50.0f+j, 50.0f+j);
		float rand_rotation = ((std::rand()) / (RAND_MAX + 1.0))*2*3.14;
		Vehicle* vehicle = new Vehicle(this,
										rand_position,
										rand_rotation,
										Vector2d(0.0f, 0.0f),
										param.vehicle_mass,
										param.max_steering_force,
										param.max_speed,
										param.max_turn_rate,
										param.vehicle_scale);
		
		vehicle->get_steering()->set_target(hero);
		vehicles.push_back(vehicle);
	}
}

Map::~Map() {
	for(int i = 0; i < vehicles.size(); ++i) {
		delete vehicles[i];
	}
	delete hero;
}

void Map::tag_vehicles_in_range(BaseGameEntity* vehicle, float range) {
	tag_neighbors(vehicle, vehicles, range);
}

void Map::tag_obstacles_in_range(BaseGameEntity* vehicle, float range) {
	tag_neighbors(vehicle, vehicles, range);
}

void Map::tag_neighbors(BaseGameEntity* entity, std::vector<Vehicle*> entities, float radius) {
	std::vector<Vehicle*>::iterator current_entity = entities.begin();
	for(current_entity; current_entity != entities.end(); ++current_entity) {
		Vehicle* vehicle = *current_entity;
		vehicle->untag();
		Vector2d to_target = vehicle->get_position() - entity->get_position();
		float range = radius + vehicle->get_bounding_radius();
		if((vehicle != entity) && (to_target.length() < range)) {
			vehicle->tag();
		}
	}
}

void Map::update(float delta_time) {
	for(int i = 0; i < vehicles.size(); ++i)
		vehicles[i]->update(delta_time);
	hero->update(delta_time);
}

void Map::draw(sf::RenderTarget& canvas) {
	hero->draw(canvas);
	for(int i = 0; i < vehicles.size(); ++i) {
		vehicles[i]->draw(canvas);
	}
}