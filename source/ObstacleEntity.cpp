#include "ObstacleEntity.h"

ObstacleEntity::ObstacleEntity(float x, float y, float radius) :
	BaseGameEntity(Vector2d(x,y), Vector2d(0.0f, 0.0f), radius) {
}

ObstacleEntity::ObstacleEntity(Vector2d position, float radius) :
	BaseGameEntity(position, Vector2d(0.0f, 0.0f), radius) {
}

void ObstacleEntity::draw(sf::RenderTarget& canvas) {
	shape.setPosition(sf::Vector2f(position.get_x(), position.get_y()));
	shape.setRadius(this->bounding_radius);
	shape.setFillColor(sf::Color(125, 125, 125));
}