/*
 * Copyright (c) 2015, Roman Meyta <theshrodingerscat@gmail.com>
 * All rights reserved
 */

#ifndef STATE_H
#define STATE_H

struct SDL_Event;

/**
 * @brief Абстрактный класс состояния
 */
template <typename ObjectType>
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
	 */
	virtual void onEnter(ObjectType* object) = 0;

	/**
	 * @brief Обработчик выхода из состояния
	 */
	virtual void onExit(ObjectType* object) = 0;

	/**
	 * @brief Обработчик событий
	 *
	 * @param event
	 */
//	virtual void onSdlEvent(ObjectType* object, const SDL_Event& event) = 0;

	/**
	 * @brief Обновить логику
	 */
	virtual void doLogic(ObjectType* object) = 0;
};

#endif // STATE_H
