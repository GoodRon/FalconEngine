/*
 * Copyright (c) 2022, Roman Meita <theshrodingerscat@gmail.com>
 * All rights reserved
 */

#ifndef FIREFLY_POSITION_EVENT_H
#define FIREFLY_POSITION_EVENT_H

#include "IEvent.h"

namespace firefly {

class StateEvent final: public IEvent {
public:
	StateEvent(EntityID id, int state);
	~StateEvent() override;

	// get id
	// get state

private:
	SDL_Event _event;
};

}

#endif // FIREFLY_POSITION_EVENT_H
