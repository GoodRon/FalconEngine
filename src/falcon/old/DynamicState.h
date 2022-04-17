/*
 * Copyright (c) 2014, Roman Meyta <theshrodingerscat@gmail.com>
 * All rights reserved
 */

#ifndef FALCON_DYNAMIC_STATE_H
#define FALCON_DYNAMIC_STATE_H

#include <string>
#include <functional>

#include "State.h"

struct SDL_Event;

namespace falcon {

template <class Object>
class DynamicState : public State<Object> {
public:
	using CommonHandler = std::function<void (Object* object)>;
	using EventHandler = std::function<void (Object* object, const SDL_Event& event)>;

	DynamicState(const std::string& name,
		  		 const State::CommonHandler& onEnter,
		  		 const State::CommonHandler& doLogic,
		  		 const State::EventHandler& onEvent,
		  		 const State::CommonHandler& onExit) : State<Object>(name), 
													   _onEnter(onEnter),
													   _doLogic(doLogic),
													   _onEvent(onEvent),
													   _onExit(onExit) {}

	virtual ~DynamicState() {}

	virtual void onEnter(Object* object) {
		if (!_onEnter) {
			return;
		}
		_onEnter(object);
	}

	virtual void doLogic(Object* object) {
		if (!_doLogic) {
			return;
		}
		_doLogic(object);
	}

	virtual void onEvent(Object* object, const SDL_Event& event) {
		if (!_onEvent) {
			return;
		}
		_onEvent(object, event);
	}

	virtual void onExit(Object* object) {
		if (!_onExit) {
			return;
		}
		_onExit(object);
	}

private:
	CommonHandler _onEnter;
	CommonHandler _doLogic;
	EventHandler _onEvent;
	CommonHandler _onExit;
};

}

#endif // FALCON_DYNAMIC_STATE_H
