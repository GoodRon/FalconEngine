/*
 * Copyright (c) 2015, Roman Meyta <theshrodingerscat@gmail.com>
 * All rights reserved
 */

#include "StateMachine.h"

StateMachine::StateMachine(ObjectType* object):
	m_object(object),
	m_currentState(nullptr),
	m_previousState(nullptr),
	m_globalState(nullptr) {
}

void StateMachine::setCurrentState(State* state) {
	m_currentState = state();
}

void StateMachine::setPreviousState(State* state) {
	m_previousState = state;
}

void StateMachine::setGlobalState(State* state) {
	m_globalState = state;
}

void StateMachine::updateState() const {
	if (m_globalState) {
		m_globalState->doLogic(m_object);
	}

	if (m_currentState) {
		m_currentState->doLogic(m_object);
	}
}

void StateMachine::changeState(State* state) {
	if (state) {
		return;
	}

	m_previousState = m_currentState;
	m_currentState->onExit(m_object);
	m_currentState = state;
	m_currentState->onEnter(m_object);
}

void StateMachine::backToPreviousState() {
	changeState(m_previousState);
}
