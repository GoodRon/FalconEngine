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
	m_height(0) {
}

WorldObject::WorldObject(int x, int y) :
	m_x(x),
	m_y(y),
	m_width(0),
	m_height(0) {
}

void WorldObject::setPosition(int x, int y) {
	m_x = x;
	m_y = y;
}

SDL_Rect WorldObject::getPositionAndProfile() const {
	SDL_Rect rect = {m_x, m_y, m_width, m_height};
	return rect;
}

int WorldObject::getDrawPriority() {
    return 0;
}
