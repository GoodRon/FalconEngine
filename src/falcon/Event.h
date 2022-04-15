/*
 * Copyright (c) 2015, Roman Meyta <theshrodingerscat@gmail.com>
 * All rights reserved
 */

#ifndef FALCON_EVENT_H
#define FALCON_EVENT_H

namespace falcon {

enum class EventType: int {
	Dummy = 0,
	SdlEvent = 1
};

class Event {
public:
	Event(EventType type);

	virtual ~Event() = 0;

	EventType getType() const;

private:
	EventType _type;
};

}

#endif // FALCON_EVENT_H
