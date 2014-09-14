/*
 * Copyright (c) 2014, Roman Meyta <theshrodingerscat@gmail.com>
 * All rights reserved
 */

#ifndef TARGET_H
#define TARGET_H

#include <memory>

class WorldObject;
struct SDL_Rect;

class Target {
public:
	Target(std::shared_ptr<WorldObject> object);

	Target(int x, int y);

	SDL_Rect getPosition();

private:
	std::shared_ptr<WorldObject> m_object;
	int m_x;
	int m_y;
};

#endif // TARGET_H
