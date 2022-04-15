/*
 * Copyright (c) 2015, Roman Meyta <theshrodingerscat@gmail.com>
 * All rights reserved
 */

#include "Event.h"

namespace falcon {

Event::Event(EventType type):
	_type(type) {
}

EventType Event::getType() const {
	return _type;
}

}
