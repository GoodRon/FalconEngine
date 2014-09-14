/*
 * Copyright (c) 2014, Roman Meyta <theshrodingerscat@gmail.com>
 * All rights reserved
 */

#include <SDL2/SDL.h>

#include "Target.h"
#include "WorldObject.h"

Target::Target(std::shared_ptr<WorldObject> object):
	m_object(object),
	m_x(0),
	m_y(0) {
}

Target::Target(int x, int y):
	m_object(),
	m_x(x),
	m_y(y) {
}

SDL_Rect Target::getPosition() {
	SDL_Rect coordinates = {m_x, m_y, 0, 0};
	if (m_object) {
		coordinates = m_object->getPosition();
	}
	return coordinates;
}
