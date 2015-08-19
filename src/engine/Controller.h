/*
 * Copyright (c) 2015, Roman Meyta <theshrodingerscat@gmail.com>
 * All rights reserved
 */

#ifndef CONTROLLER_H
#define CONTROLLER_H

class WorldObject;

class Controller {
public:
	Controller(WorldObject* object): m_object(object) {}
	virtual ~Controller() {}

	virtual void onEvent(const SDL_Event& event) = 0;

protected:
	WorldObject* m_object;
};

#endif // CONTROLLER_H
