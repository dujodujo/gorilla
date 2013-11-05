#ifndef BALL_ENTITY_H
#define BALL_ENTITY_H

#include <SFML\System\Vector2.hpp>
#include <SFML\Graphics\RectangleShape.hpp>
#include <SFML\Graphics\RenderTarget.hpp>

const float MAX_FORCE = 0.4f;
const int MAX_VELOCITY = 3;

class BallEntity {
	
private:
	sf::RectangleShape shape;

	sf::Vector2f position;
	sf::Vector2f velocity;
	sf::Vector2f target;
	sf::Vector2f steering;
	sf::Vector2f desired_velocity;
	int mass;

public:
	BallEntity(int x, int y, int mass);
	~BallEntity();

	sf::Vector2f seek(sf::Vector2f& vector);
	sf::Vector2f subtract(sf::Vector2f& vector, sf::Vector2f& other);
	sf::Vector2f add(sf::Vector2f& vector, sf::Vector2f& other);

	void truncate(sf::Vector2f& vector, int max);
	float length_vector(sf::Vector2f vector);
	void normalize_vector(sf::Vector2f& vector);

	void draw(sf::RenderTarget& canvas);
	void update(sf::Vector2i vector);
};

#endif