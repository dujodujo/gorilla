#include "BaseGameEntity.h"

BaseGameEntity::BaseGameEntity() : 
	position(Vector2d()),
	scale(Vector2d(1.0f,1.0f)),
	bounding_radius(0) {
}

BaseGameEntity::BaseGameEntity(Vector2d position, Vector2d scale, float radius) :
	position(position),
	scale(scale),
	bounding_radius(radius) {
}

void BaseGameEntity::set_scale(Vector2d val) {
	bounding_radius *= 
		maxOf(val.get_x(), val.get_y())/maxOf(scale.get_x(), scale.get_y());
	this->scale = val;
}

void BaseGameEntity::set_scale(float val) {
	bounding_radius *= (val/maxOf(scale.get_x(), scale.get_y()));
	scale = Vector2d(val, val);
}