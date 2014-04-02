/*
 * Copyright (c) 2014, Roman Meyta <theshrodingerscat@gmail.com>
 * All rights reserved
 */

#ifndef STATE_H
#define STATE_H

struct SDL_Event;

/**
 * @brief Абстрактный класс состояния
 */
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
	virtual void onEnter() = 0;

	/**
	 * @brief Обработчик выхода из состояния
	 */
	virtual void onExit() = 0;

// Update() Draw() 

	/**
	 * @brief Обработчик событий
	 * 
	 * @param event
	 */
	virtual void onEvent(const SDL_Event& event) = 0;
};

#endif // STATE_H
