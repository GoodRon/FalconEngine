/*
 * Copyright (c) 2015, Roman Meyta <theshrodingerscat@gmail.com>
 * All rights reserved
 */

#ifndef STATE_H
#define STATE_H

class Event;

/**
 * @brief Абстрактный класс состояния
 */
template <typename Object>
class State {
public:
	/**
	 * @brief Конструктор
	 */
	State() {}

	/**
	 * @brief Деструктор
	 */
	virtual ~State() {}

	/**
	 * @brief Обработчик входа в состояние
	 *
	 * @param object
	 */
	virtual void onEnter(Object* object) = 0;

	/**
	 * @brief Обработчик выхода из состояния
	 *
	 * @param object
	 */
	virtual void onExit(Object* object) = 0;

	/**
	 * @brief Обработчик событий
	 *
	 * @param object
	 * @param event
	 */
	virtual void onEvent(Object* object, const Event& event) {}

	/**
	 * @brief Обновить логику
	 *
	 * @param object
	 */
	virtual void doLogic(Object* object) = 0;
};

#endif // STATE_H
