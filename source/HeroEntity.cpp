#include "HeroEntity.h"

#include <cmath>
#include <math.h>

HeroEntity::HeroEntity(Vector2d position,
				float rotation,
				Vector2d velocity,
				float mass,
				float max_force,
				float max_speed,
				float max_turn_rate,
				float scale) : 
				MovingEntity(position, 
				scale, 
				velocity,
				max_speed,
				Vector2d(std::sin(scale), -std::cos(scale)),
				mass,
				Vector2d(scale, scale),
				max_force,
				max_turn_rate) {
	shape.setPosition(sf::Vector2f(position.get_x(), position.get_y()));
	shape.setSize(sf::Vector2f(20.0f, 20.0f));
}

HeroEntity::~HeroEntity() {}

void HeroEntity::update(float delta_time) {
	this->movement();
	this->velocity.truncate(this->max_speed);
	this->position += velocity * delta_time * 20;
	shape.setPosition(sf::Vector2f(position.get_x(), position.get_y()));
	if(velocity.length_sq() > 1E-6) {
		this->heading = vec2d_normalize(velocity);
		this->side = heading.perp();
	}
}

void HeroEntity::draw(sf::RenderTarget& canvas) {
	canvas.draw(shape);
}

void HeroEntity::movement() {
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
			this->velocity.set_xy(-1.0f, -1.0f);
		} else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
			this->velocity.set_xy(-1.0f, 1.0f);
		} else {
			this->velocity.set_xy(-1.0f, 0.0f);
		}
	} else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
			this->velocity.set_xy(1.0f, -1.0f);
		} else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
			this->velocity.set_xy(1.0f, 1.0f);
		} else {
			this->velocity.set_xy(1.0f, 0.0f);
		}
	} else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
			this->velocity.set_xy(1.0f, -1.0f);
		} else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
			this->velocity.set_xy(-1.0f, -1.0f);
		} else {
			this->velocity.set_xy(0.0f, -1.0f);
		}
	} else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
			this->velocity.set_xy(1.0f, 1.0f);
		} else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
			this->velocity.set_xy(-1.0f, 1.0f);
		} else {
			this->velocity.set_xy(0.0f, 1.0f);
		}
	} else {
		this->velocity.set_xy(0.0f, 0.0f);
	}
}