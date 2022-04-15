/*
 * Copyright (c) 2015, Roman Meyta <theshrodingerscat@gmail.com>
 * All rights reserved
 */

#ifndef FALCON_STATE_H
#define FALCON_STATE_H

namespace falcon {

class Event;

template <typename Object>
class State {
public:
	virtual ~State() {}

	virtual void onEnter(Object* object) {}
	virtual void onExit(Object* object) {}
	virtual void onEvent(Object* object, const Event& event) {}
	virtual void doLogic(Object* object) {}
};

}

#endif // FALCON_STATE_H
