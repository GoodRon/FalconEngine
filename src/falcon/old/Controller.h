/*
 * Copyright (c) 2015, Roman Meyta <theshrodingerscat@gmail.com>
 * All rights reserved
 */

#ifndef FALCON_CONTROLLER_H
#define FALCON_CONTROLLER_H

union SDL_Event;

namespace falcon {

class WorldObject;

class Controller {
public:
	Controller(WorldObject* object): 
		_object(object) {}
	virtual ~Controller() {}

	virtual void onEvent(const SDL_Event& event) = 0;

protected:
	WorldObject* _object;
};

}

#endif // FALCON_CONTROLLER_H
