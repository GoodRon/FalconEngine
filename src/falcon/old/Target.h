/*
 * Copyright (c) 2014, Roman Meyta <theshrodingerscat@gmail.com>
 * All rights reserved
 */

#ifndef FALCON_TARGET_H
#define FALCON_TARGET_H

#include <memory>

struct SDL_Rect;

namespace falcon {

class WorldObject;

class Target {
public:
	Target(std::shared_ptr<WorldObject> object);

	Target(int x, int y);

	SDL_Rect getPosition();

private:
	std::shared_ptr<WorldObject> _object;
	int _x;
	int _y;
};

}

#endif // FALCON_TARGET_H
