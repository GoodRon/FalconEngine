/*
 * Copyright (c) 2014, Roman Meyta <theshrodingerscat@gmail.com>
 * All rights reserved
 */

#ifndef STATE_H
#define STATE_H

#include <string>

struct SDL_Event;

/**
 * @brief Абстрактный класс состояния
 */
template <class Object>
class State {
public:
	/**
	 * @brief Конструктор
	 */
	State(): {}

	/**
	 * @brief Деструктор
	 */
	virtual ~State() {}

	/**
	 * @brief Обработчик входа в состояние
	 */
	virtual void onEnter(Object* object) = 0;

	/**
	 * @brief Обработчик выхода из состояния
	 */
	virtual void onExit(Object* object) = 0;

	/**
	 * @brief Обработчик событий
	 *
	 * @param event
	 */
	virtual void onSdlEvent(Object* object, const SDL_Event& event) = 0;

	/**
	 * @brief Обновить логику
	 */
	virtual void doLogic(Object* object) = 0;
};

#endif // STATE_H
