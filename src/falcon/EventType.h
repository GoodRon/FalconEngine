/*
 * Copyright (c) 2022, Roman Meita <theshrodingerscat@gmail.com>
 * All rights reserved
 */

#ifndef FALCON_EVENT_TYPE_H
#define FALCON_EVENT_TYPE_H

namespace falcon {

enum class EventType: int {
	Input,
	Update,
	Draw,
	Collide,
	Destroy,
}

}

#endif // FALCON_EVENT_TYPE_H
