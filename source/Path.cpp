#include <SFML\Graphics\RectangleShape.hpp>
#include <SFML\Graphics\CircleShape.hpp>
#include "Transformations.h"
#include "Matrix2d.h"
#include "Path.h"
#include <iostream>
#include <cassert>

Path::Path(int num_waypoints, float minX, float minY, float maxX, float maxY,
	bool path_looped) : 
	path_looped(path_looped) {

	waypoints = create_random_path(num_waypoints, minX, minY, maxX, maxY);
	current_waypoint = waypoints.begin();
}

std::list<Vector2d> Path::create_random_path(int num_waypoints, float minX, float minY, float maxX, float maxY) {
	this->waypoints.clear();
	float midX = (minX + maxX) / 2.0f;
	float midY = (minY + maxY) / 2.0f;
	float smaller = std::min(midX, midY);
	float spacing = 360 / num_waypoints;
	for (int i = 0; i < num_waypoints; i++) {
		float dist = ((float)std::rand()/RAND_MAX+1)*smaller*0.4f;
		Vector2d temp(dist, 0.0f);
		rotate_around_origin(temp, i*spacing);
		temp.vector.x += midX;
		temp.vector.y += midY;
		waypoints.push_back(temp);
	}
	current_waypoint = waypoints.begin();
	return waypoints;
}

Vector2d Path::get_current_waypoint(){
	if(&current_waypoint != NULL) {
		return *current_waypoint;
	}
}

bool Path::finished() {
	return this->current_waypoint == waypoints.end();
}

void Path::set_next_waypoint() {
	if(++current_waypoint == waypoints.end()) {
		if(path_looped) {
			this->current_waypoint= waypoints.begin();
		}
	}
}

void Path::set_path(std::list<Vector2d> path) {
	waypoints = path;
	this->current_waypoint = waypoints.begin();
}

void Path::set_path(Path& path) {
	this->waypoints = path.get_path();
	this->current_waypoint = waypoints.begin();
}

void Path::loop_off() {
	this->path_looped = false;
}

void Path::loop_on() {
	this->path_looped = true;
}

void Path::clear_waypoints() {
	this->waypoints.clear();
}

std::list<Vector2d> Path::get_path() {
	return this->waypoints;
}

void Path::draw(sf::RenderTarget& canvas) const {
	std::list<Vector2d>::const_iterator iter = waypoints.begin();
	Vector2d waypoint = *iter;
	
	sf::CircleShape shape;
	while(iter != waypoints.end()) {
		waypoint = *iter++;
		shape.setPosition(waypoint.vector.x, waypoint.vector.y);
		shape.setRadius(5.0f);
		shape.setFillColor(sf::Color(255, 255, 255));
		canvas.draw(shape);
	}
}