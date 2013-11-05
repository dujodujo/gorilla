#ifndef CIRCLE_BALL_H
#define CIRCLE_BALL_H

#include <SFML\System.hpp>
#include <SFML\Graphics\CircleShape.hpp>
#include <SFML\Graphics\RenderTarget.hpp>

class CircleBall {

private:
	sf::Vector2f position;
	sf::CircleShape shape;

public:
	CircleBall(int x, int y, int radius, int points);
	~CircleBall();

	void draw(sf::RenderTarget& canvas);
	void update(sf::Vector2i mouse_position);

};

#endif