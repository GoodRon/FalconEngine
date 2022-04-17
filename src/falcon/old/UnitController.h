/*
 * Copyright (c) 2015, Roman Meyta <theshrodingerscat@gmail.com>
 * All rights reserved
 */

#ifndef FALCON_UNIT_CONTROLLER_H
#define FALCON_UNIT_CONTROLLER_H

#include "Controller.h"

namespace falcon {

class UnitController: public Controller {
public:
	UnitController(WorldObject* object);
	~UnitController() override;

	void onEvent(const SDL_Event& event) override;
};

}

#endif // FALCON_UNIT_CONTROLLER_H
