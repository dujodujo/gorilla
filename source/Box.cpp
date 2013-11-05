#include "Box.h"

Box::Box(b2World& world, float x, float y) :
	world(world) {
	
	body_def.position = b2Vec2(x/SCALE, y/SCALE);
	body_def.type = b2_dynamicBody;
	body = world.CreateBody(&body_def);

	box_texture.loadFromFile("box.png");
	this->sprite.setTexture(box_texture);

	b2PolygonShape shape;
	shape.SetAsBox((32.f/2)/SCALE, (32.f/2)/SCALE);
    b2FixtureDef fixture_def;
    fixture_def.density = 1.f;
    fixture_def.friction = 0.7f;
    fixture_def.shape = &shape;
    body->CreateFixture(&fixture_def);
}

void Box::set_position(int x, int y) {
	this->sprite.setPosition(SCALE*x, SCALE*y);
}

void Box::set_origin(int x, int y) {
	this->sprite.setOrigin(x, y);
}

void Box::set_rotation(float rotation) {
	this->sprite.setRotation(rotation);
}

void Box::set_texture(sf::Texture texture) {
	this->sprite.setTexture(texture);
}

sf::Sprite Box::get_sprite() {
	return this->sprite;
}

b2Body* Box::get_body() {
	return this->body;
}