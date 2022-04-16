/*
 * Copyright (c) 2022, Roman Meita <theshrodingerscat@gmail.com>
 * All rights reserved
 */

#ifndef FALCON_IEVENT_H
#define FALCON_IEVENT_H

namespace falcon {

using EventType = int;

class Event {
public:
	Event(EventType type);

	virtual ~Event() = 0;

	const EventType getType() const;

private:
	const EventType _type;
};

}

#endif // FALCON_IEVENT_H
