/*
 * Copyright (c) 2022, Roman Meita <theshrodingerscat@gmail.com>
 * All rights reserved
 */

#ifndef FIREFLY_EVENT_TYPE_H
#define FIREFLY_EVENT_TYPE_H

namespace firefly {

enum class EventType: int {
	Unknown = 0,
	Update,
	Native,
	Entity,
	State,
	Kill,
	Collision,
	Position,
	Speed
}; 

}

#endif // FIREFLY_EVENT_TYPE_H
