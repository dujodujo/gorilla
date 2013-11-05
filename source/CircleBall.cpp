#include "CircleBall.h"

CircleBall::CircleBall(int x, int y, int radius, int points) :
	position(x,y) {
	shape = sf::CircleShape(radius, points);
	shape.setPosition(position);
	shape.setFillColor(sf::Color(255, 255, 255));
}

CircleBall::~CircleBall() {}

void CircleBall::draw(sf::RenderTarget& canvas) {
	canvas.draw(shape);
}

void CircleBall::update(sf::Vector2i mouse_position) {
	int x = mouse_position.x;
	int y = mouse_position.y;
	shape.setPosition(sf::Vector2f(x,y));

}