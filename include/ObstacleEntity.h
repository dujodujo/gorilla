#ifndef OBSTACLE_H
#define OBSTACLE_H

#include <SFML\Graphics\RenderTarget.hpp>
#include <SFML\Graphics\CircleShape.hpp>
#include "BaseGameEntity.h"
#include "Vector2d.h"

class ObstacleEntity : public BaseGameEntity {

private:
	sf::CircleShape shape;

public:
	ObstacleEntity(float x, float y, float radius);
	ObstacleEntity(Vector2d position, float radius);

	virtual ~ObstacleEntity() {};

	void draw(sf::RenderTarget& canvas);
	void update(float elapsed_time) {};
};

#endif