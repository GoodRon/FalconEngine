/*
 * Copyright (c) 2015, Roman Meyta <theshrodingerscat@gmail.com>
 * All rights reserved
 */

#ifndef UNITCONTROLLER_H
#define UNITCONTROLLER_H

#include "Controller.h"

class UnitController: public Controller {
public:
	UnitController(WorldObject* object);
	virtual ~UnitController();

	virtual void onEvent(const SDL_Event& event) override;
};

#endif // UNITCONTROLLER_H
