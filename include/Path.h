#ifndef PATH_H
#define PATH_H

#include <SFML\Graphics\RenderTarget.hpp>
#include "Vector2d.h"
#include <cassert>
#include <list>

class Path {

private:
	std::list<Vector2d> waypoints;
	std::list<Vector2d>::iterator current_waypoint;
	bool path_looped;

public:
	//TOOD path cstr to read from file.
	Path() : path_looped(false) {}
	Path(int num_waypoints,
		float minX,
		float minY, 
		float maxX, 
		float maxY,
		bool path_looped);

	Vector2d get_current_waypoint();
	bool finished();
	void set_next_waypoint();

	void set_path(std::list<Vector2d> path);
	void set_path(Path& path);

	void loop_on();
	void loop_off();

	void clear_waypoints();
	std::list<Vector2d> get_path();

	std::list<Vector2d>  create_random_path(int num_waypoints, float minX, float minY, float maxX, float maxY);

	void draw(sf::RenderTarget& canvas) const;
};


#endif