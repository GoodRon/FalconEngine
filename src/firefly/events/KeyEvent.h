/*
 * Copyright (c) 2022, Roman Meita <theshrodingerscat@gmail.com>
 * All rights reserved
 */

#ifndef FIREFLY_IEVENT_H
#define FIREFLY_IEVENT_H

#include "Types.h"

namespace firefly {

class Event {
public:
	Event(EventType type);

	virtual ~Event() = 0;

	const EventType getType() const;

private:
	const EventType _type;
};

}

#endif // FIREFLY_IEVENT_H
