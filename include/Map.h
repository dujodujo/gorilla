#ifndef MAP_H
#define MAP_H

#include <SFML\Graphics\RenderTarget.hpp>
#include "BaseGameEntity.h"
#include "ObstacleEntity.h"
#include "HeroEntity.h"
#include "Vector2d.h"
#include "Vehicle.h"

#include <vector>
#include <iostream>
#include <cmath>

//typedef std::vector<BaseGameEntity*>::iterator observer_item;

class Map {

private:
	std::vector<Vehicle*> vehicles;
	std::vector<ObstacleEntity*> obstacles;
	HeroEntity* hero;

public:
	Map();
	~Map();

	std::vector<Vehicle*>& get_vehicles() {return vehicles;}
	std::vector<ObstacleEntity*>& get_obstacles() {return obstacles;}

	void tag_neighbors(BaseGameEntity* entity, std::vector<Vehicle*> entities, float radius);
	void tag_vehicles_in_range(BaseGameEntity* vehicle, float range);
	void tag_obstacles_in_range(BaseGameEntity* vehicle, float range);

	void update(float delta_time);
	void draw(sf::RenderTarget& target);
};

#endif