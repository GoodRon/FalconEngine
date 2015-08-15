/*
 * Copyright (c) 2015, Roman Meyta <theshrodingerscat@gmail.com>
 * All rights reserved
 */

#include "StateMachine.h"
#include "State.h"

template <typename ObjectType>
StateMachine<ObjectType>::StateMachine(ObjectType* object):
	m_object(object),
	m_currentState(nullptr),
	m_previousState(nullptr),
	m_globalState(nullptr) {
}

template <typename ObjectType>
void StateMachine<ObjectType>::setCurrentState(State<ObjectType>* state) {
	m_currentState = state();
}

template <typename ObjectType>
void StateMachine<ObjectType>::setPreviousState(State<ObjectType>* state) {
	m_previousState = state;
}

template <typename ObjectType>
void StateMachine<ObjectType>::setGlobalState(State<ObjectType>* state) {
	m_globalState = state;
}

template <typename ObjectType>
void StateMachine<ObjectType>::updateState() const {
	if (m_globalState) {
		m_globalState->doLogic(m_object);
	}

	if (m_currentState) {
		m_currentState->doLogic(m_object);
	}
}

template <typename ObjectType>
void StateMachine<ObjectType>::changeState(State<ObjectType>* state) {
	if (state) {
		return;
	}

	m_previousState = m_currentState;
	m_currentState->onExit(m_object);
	m_currentState = state;
	m_currentState->onEnter(m_object);
}

template <typename ObjectType>
void StateMachine<ObjectType>::backToPreviousState() {
	changeState(m_previousState);
}
