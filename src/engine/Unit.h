/*
 * Copyright (c) 2014, Roman Meyta <theshrodingerscat@gmail.com>
 * All rights reserved
 */

#ifndef UNIT_H
#define UNIT_H

#include "WorldObject.h"

struct SDL_Rect;

class Unit: public WorldObject {
public:
	Unit();
	
	virtual ~Unit();
	
	

	SDL_Rect getCollisionBounds() const;

private:

};

#endif // UNIT_H