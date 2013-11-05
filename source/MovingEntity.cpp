#include "MovingEntity.h"

void MovingEntity::set_heading(Vector2d heading) {
	if((heading.length_sq() - 1.0) < 1E-4) {
		this->heading = heading;
		this->side = heading.perp();
	}
}