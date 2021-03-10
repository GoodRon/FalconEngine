/*
 * Copyright (c) 2015, Roman Meyta <theshrodingerscat@gmail.com>
 * All rights reserved
 */

#ifndef FALCON_STATE_MACHINE_H
#define FALCON_STATE_MACHINE_H

#include <memory>

#include "State.h"

namespace falcon {

template <typename ObjectType>
class StateMachine {
public:
	StateMachine(ObjectType* object);

	void setCurrentState(std::unique_ptr<State<ObjectType>>&& state);

	void setPreviousState(std::unique_ptr<State<ObjectType>>&& state);

	void setGlobalState(std::unique_ptr<State<ObjectType>>&& state);

	void changeState(std::unique_ptr<State<ObjectType>>&& state);

	void updateState() const;

	void backToPreviousState();

	void handleEvent(const Event& event) const;

private:
	ObjectType* _object;
	std::unique_ptr<State<ObjectType>> _currentState;
	std::unique_ptr<State<ObjectType>> _previousState;
	std::unique_ptr<State<ObjectType>> _globalState;
};

template <typename ObjectType>
StateMachine<ObjectType>::StateMachine(ObjectType* object):
	_object(object),
	_currentState(),
	_previousState(),
	_globalState() {
}

template <typename ObjectType>
void StateMachine<ObjectType>::setCurrentState(
	std::unique_ptr<State<ObjectType>>&& state) {

	_currentState = std::move(state);
}

template <typename ObjectType>
void StateMachine<ObjectType>::setPreviousState(
	std::unique_ptr<State<ObjectType>>&& state) {

	_previousState = std::move(state);
}

template <typename ObjectType>
void StateMachine<ObjectType>::setGlobalState(
	std::unique_ptr<State<ObjectType>>&& state) {

	_globalState = std::move(state);
}

template <typename ObjectType>
void StateMachine<ObjectType>::changeState(
	std::unique_ptr<State<ObjectType>>&& state) {

	_previousState = std::move(_currentState);
	_currentState = std::move(state);

	if (_previousState) {
		_previousState->onExit(_object);
	}

	if (_currentState) {
		_currentState->onEnter(_object);
	}
}

template <typename ObjectType>
void StateMachine<ObjectType>::updateState() const {
	if (_globalState) {
		_globalState->doLogic(_object);
	}

	if (_currentState) {
		_currentState->doLogic(_object);
	}
}

template <typename ObjectType>
void StateMachine<ObjectType>::backToPreviousState() {
	changeState(std::move(_previousState));
}

template <typename ObjectType>
void StateMachine<ObjectType>::handleEvent(const Event& event) const {
	if (_globalState) {
		_globalState->onEvent(_object, event);
	}

	if (_currentState) {
		_currentState->onEvent(_object, event);
	}
}

}

#endif // FALCON_STATE_MACHINE_H
