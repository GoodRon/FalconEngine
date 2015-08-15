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
	StateMachine(ObjectType* object);

	/**
	 * @brief Установить текущее состояние
	 *
	 * @param state
	 */
	void setCurrentState(State<ObjectType>* state);

	/**
	 * @brief Установить предыдущее состояние
	 *
	 * @param state
	 */
	void setPreviousState(State<ObjectType>* state);

	/**
	 * @brief Установить глобальное состояние
	 *
	 * @param state
	 */
	void setGlobalState(State<ObjectType>* state);

	/**
	 * @brief Обновить логику состояния
	 */
	void updateState() const;

	/**
	 * @brief Сменить состояние
	 *
	 * @param state
	 */
	void changeState(State<ObjectType>* state);

	/**
	 * @brief Вернуться к предыдущему состоянию
	 */
	void backToPreviousState();

private:
	/**
	 * @brief Указатель на объект
	 */
	ObjectType* m_object;

	/**
	 * @brief Указатель на текущее состояние
	 */
	State<ObjectType>* m_currentState;

	/**
	 * @brief Указатель на предыдущее состояние
	 */
	State<ObjectType>* m_previousState;

	/**
	 * @brief Указатель на глобальное состояние
	 */
	State<ObjectType>* m_globalState;
};

#endif // STATEMACHINE_H
