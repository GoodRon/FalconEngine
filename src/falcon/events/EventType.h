/*
 * Copyright (c) 2022, Roman Meita <theshrodingerscat@gmail.com>
 * All rights reserved
 */

#ifndef FALCON_EVENT_TYPE_H
#define FALCON_EVENT_TYPE_H

namespace falcon {

class Event {
public:
	Event(EventType type);

	virtual ~Event() = 0;

	const EventType getType() const;

private:
	const EventType _type;
};

}

#endif // FALCON_EVENT_TYPE_H
