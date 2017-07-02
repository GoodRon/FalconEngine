/*
 * Copyright (c) 2014, Roman Meyta <theshrodingerscat@gmail.com>
 * All rights reserved
 */

#include <random>

#include <SDL2/SDL.h>

#include "WorldObject.h"

using namespace std;

WorldObject::WorldObject(int x, int y) :
	_id(),
	_x(x),
	_y(y),
	_width(0),
	_height(0),
	_isVisible(true) {
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<int> dis;
	m_id = dis(gen);
}

WorldObject::WorldObject() :
	WorldObject(0, 0) {
}

WorldObject::~WorldObject() {
}

int WorldObject::getId() const {
	return _id;
}

void WorldObject::setPosition(int x, int y) {
	_x = x;
	_y = y;
}

SDL_Rect WorldObject::getPositionAndProfile() const {
	SDL_Rect position = getPosition();
	SDL_Rect profile = getProfile();
	SDL_Rect rect = {position.x, position.y, profile.w, profile.h};
	return rect;
}

SDL_Rect WorldObject::getProfile() const {
	SDL_Rect rect = {0, 0, _width, _height};
	return rect;
}

SDL_Rect WorldObject::getPosition() const {
	SDL_Rect rect = {_x, _y, 0, 0};
	return rect;
}

//void WorldObject::executeCommand(Command* command) {
//}

void WorldObject::doLogic() {
}

int WorldObject::getDrawPriority() {
	return 0;
}

void WorldObject::setVisibility(bool isVisible) {
	_isVisible = isVisible;
}

bool WorldObject::isVisible() const {
	return _isVisible;
}

void WorldObject::setCollidability(bool isCollidable) {
	_isCollidable = isCollidable;
}

bool WorldObject::isCollidable() const {
	return _isCollidable;
}
