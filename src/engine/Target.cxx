/*
 * Copyright (c) 2014, Roman Meyta <theshrodingerscat@gmail.com>
 * All rights reserved
 */

#include <SDL2/SDL.h>

#include "Target.h"
#include "WorldObject.h"

namespace falcon {

Target::Target(std::shared_ptr<WorldObject> object):
	_object(object),
	_x(0),
	_y(0) {
}

Target::Target(int x, int y):
	_object(),
	_x(x),
	_y(y) {
}

SDL_Rect Target::getPosition() {
	if (_object) {
		return _object->getPosition();
	}
	return SDL_Rect{_x, _y, 0, 0};
}

}
