/*
 * Copyright (c) 2014, Roman Meyta <theshrodingerscat@gmail.com>
 * All rights reserved
 */

#include <SDL2/SDL.h>

#include "WorldObject.h"

WorldObject::WorldObject() :
	m_x(0),
	m_y(0),
	m_width(0),
	m_height(0),
	m_isVisible(true) {
}

WorldObject::WorldObject(int x, int y) :
	m_x(x),
	m_y(y),
	m_width(0),
	m_height(0),
	m_isVisible(true) {
}

WorldObject::~WorldObject() {
}

void WorldObject::setPosition(int x, int y) {
	m_x = x;
	m_y = y;
}

SDL_Rect WorldObject::getPositionAndProfile() const {
	SDL_Rect position = getPosition();
	SDL_Rect profile = getProfile();
	SDL_Rect rect = {position.x, position.y, profile.w, profile.h};
	return rect;
}

SDL_Rect WorldObject::getProfile() const {
	SDL_Rect rect = {0, 0, m_width, m_height};
	return rect;
}

SDL_Rect WorldObject::getPosition() const {
	SDL_Rect rect = {m_x, m_y, 0, 0};
	return rect;
}

void WorldObject::doLogic() {
}

int WorldObject::getDrawPriority() {
	return 0;
}

void WorldObject::setVisibility(bool isVisible) {
	m_isVisible = isVisible;
}

bool WorldObject::getVisibility() const {
	return m_isVisible;
}
