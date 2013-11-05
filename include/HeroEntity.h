#ifndef HERO_ENTITY_H
#define HERO_ENTITY_H

#include <SFML\Graphics\RectangleShape.hpp>
#include <SFML\Window\Keyboard.hpp>
#include <SFML\Window\Event.hpp>
#include "MovingEntity.h"
#include "Vector2d.h"
#include <cstdlib>
#include <vector>
#include <list>

class HeroEntity : public MovingEntity {

private:
	sf::RectangleShape shape;

public:
	HeroEntity(Vector2d position,
			float rotation,
			Vector2d velocity,
			float mass,
			float max_force,
			float max_speed,
			float max_turn_rate,
			float scale);
	HeroEntity(const HeroEntity&);
	HeroEntity& operator=(const HeroEntity&);
	~HeroEntity();

	void movement();
	void update(float delta_time);
	void draw(sf::RenderTarget& canvas);
};

#endif