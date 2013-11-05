#include "Ground.h"

Ground::Ground(b2World& world, float x, float y) :
	world(world) {

	ground_texture.loadFromFile("ground.png");
	this->sprite.setTexture(ground_texture);
	body_def.position = b2Vec2(x/SCALE, y/SCALE);
	body_def.type = b2_staticBody;
	body = world.CreateBody(&body_def);


	b2PolygonShape shape;
	shape.SetAsBox((800.f/2)/SCALE, (16.f/2)/SCALE);
    b2FixtureDef fixture_def;
    fixture_def.density = 0.f;
    fixture_def.shape = &shape;
    body->CreateFixture(&fixture_def);
}


void Ground::set_position(int x, int y) {
	this->sprite.setPosition(SCALE*x, SCALE*y);
}

void Ground::set_origin(int x, int y) {
	this->sprite.setOrigin(x, y);
}

void Ground::set_rotation(float rotation) {
	this->sprite.setRotation(rotation);
}

sf::Sprite Ground::get_sprite() {
	return this->sprite;
}

b2Body* Ground::get_body() {
	return this->body;
}