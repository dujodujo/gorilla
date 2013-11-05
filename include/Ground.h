#ifndef GROUND_H
#define GROUND_H

#include <SFML\Graphics.hpp>
#include "Box2D\Box2D.h"
#include "Vector2d.h"

#define SCALE 30.f

class Ground {

private:
	b2World& world;
	sf::Sprite sprite;
    sf::Texture ground_texture;
	b2BodyDef body_def;
    b2Body* body;
	b2PolygonShape shape;
    b2FixtureDef fixture_def;
	Vector2d position;
	Vector2d size;

public:
	Ground(b2World& world, float x, float y);
	~Ground() {}

	sf::Sprite get_sprite();
	b2Body* get_body();
	
	void set_position(int x, int y);
	void set_origin(int x, int y);
	void set_rotation(float rotation);
};

#endif