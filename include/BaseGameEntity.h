#ifndef BASE_GAME_ENTITY_H
#define BASE_GAME_ENTITY_H

#include <SFML\Graphics\RenderTarget.hpp>
#include "Vector2d.h"
#include "Utils.h"

class BaseGameEntity {

protected:
	Vector2d position;
	Vector2d scale;
	float bounding_radius;
	bool tagged;

public:
	BaseGameEntity();
	BaseGameEntity(Vector2d position, Vector2d scale, float radius);

	virtual ~BaseGameEntity() {};
	virtual void update(float delta_time) = 0;
	virtual void draw(sf::RenderTarget& canvas) = 0;

	bool is_tag() {return tagged;}
	void tag() {this->tagged = true;}
	void untag() {this->tagged = false;}

	int get_id() const {return 0;}
	int start_id() const {return 0;}

	Vector2d get_position() {return position;}
	virtual void set_position(Vector2d position) {position=position;}
	float get_bounding_radius() const {return bounding_radius;}
	void set_bounding_radius(float bounding_radius) {bounding_radius = bounding_radius;}

	Vector2d do_scale() const {return scale;}
	void set_scale(Vector2d val);
	void set_scale(float val);

};


#endif