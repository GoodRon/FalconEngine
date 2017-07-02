/*
 * Copyright (c) 2015, Roman Meyta <theshrodingerscat@gmail.com>
 * All rights reserved
 */

#ifndef STATEMACHINE_H
#define STATEMACHINE_H

#include "State.h"

/**
 * @brief Машина состояний
 */
template <typename ObjectType>
class StateMachine {
public:
	/**
	 * @brief Конструктор
	 *
	 * @param object
	 */
	//StateMachine(ObjectType* object);
	StateMachine(State<ObjectType>* baseState = nullptr);

	~StateMachine();

	/**
	 * @brief Установить текущее состояние
	 *
	 * @param state
	 */
	//void setCurrentState(State<ObjectType>* state);

	/**
	 * @brief Установить предыдущее состояние
	 *
	 * @param state
	 */
	//void setPreviousState(State<ObjectType>* state);

	/**
	 * @brief Установить глобальное состояние
	 *
	 * @param state
	 */
	//void setGlobalState(State<ObjectType>* state);

	/**
	 * @brief Обновить логику состояния
	 */
	void updateState() const;

	int getStateType() const;

	/**
	 * @brief Обработчик событий
	 *
	 * @param event
	 */
	//void handleEvent(const Event& event) const;

	/**
	 * @brief Сменить состояние
	 *
	 * @param state
	 */
	void changeState(State<ObjectType>* state);

	/**
	 * @brief Вернуться к предыдущему состоянию
	 */
	//void backToPreviousState();

private:
	/**
	 * @brief Указатель на объект
	 */
	//ObjectType* m_object;

	/**
	 * @brief Указатель на текущее состояние
	 */
	State<ObjectType>* _currentState;

	/**
	 * @brief Указатель на предыдущее состояние
	 */
	State<ObjectType>* m_previousState;

	/**
	 * @brief Указатель на глобальное состояние
	 */
	//State<ObjectType>* m_globalState;
};

template <typename ObjectType>
StateMachine<ObjectType>::StateMachine(State<ObjectType>* baseState = nullptr):
	//m_object(object),
	_currentState(baseState) {
	//m_previousState(nullptr),
	//m_globalState(nullptr) {
}

template <typename ObjectType>
StateMachine<ObjectType>::~StateMachine() {
	delete _currentState;
}

/*
template <typename ObjectType>
void StateMachine<ObjectType>::setCurrentState(State<ObjectType>* state) {
	m_currentState = state;
}

template <typename ObjectType>
void StateMachine<ObjectType>::setPreviousState(State<ObjectType>* state) {
	m_previousState = state;
}

template <typename ObjectType>
void StateMachine<ObjectType>::setGlobalState(State<ObjectType>* state) {
	m_globalState = state;
}
*/

template <typename ObjectType>
void StateMachine<ObjectType>::updateState() const {
//	if (m_globalState) {
//		m_globalState->doLogic(m_object);
//	}

	if (m_currentState) {
		m_currentState->doLogic(m_object);
	}
}

/*
template <typename ObjectType>
void StateMachine<ObjectType>::handleEvent(const Event& event) const {
	if (m_globalState) {
		m_globalState->onEvent(m_object, event);
	}

	if (m_currentState) {
		m_currentState->onEvent(m_object, event);
	}
}
*/

template <typename ObjectType>
void StateMachine<ObjectType>::changeState(State<ObjectType>* state) {
	if (!state) {
		return;
	}

	delete m_previousState;
	m_previousState = m_currentState;
	m_currentState->onExit();
	m_currentState = state;
	m_currentState->onEnter();
}

/*
template <typename ObjectType>
void StateMachine<ObjectType>::backToPreviousState() {
	changeState(m_previousState);
}
*/

#endif // STATEMACHINE_H
