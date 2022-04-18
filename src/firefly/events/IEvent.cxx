/*
 * Copyright (c) 2022, Roman Meita <theshrodingerscat@gmail.com>
 * All rights reserved
 */

#include "IEvent.h"

namespace firefly {

Event::Event(EventType type):
	_type(type) {
}

const EventType Event::getType() const {
	return _type;
}

}
