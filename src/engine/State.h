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
	State(Object* object) : _object(object), _type(0) {}

	int getType() const;

	/**
	 * @brief Деструктор
	 */
	virtual ~State() {}

	/**
	 * @brief Обработчик входа в состояние
	 *
	 * @param object
	 */
	virtual void onEnter() = 0;

	/**
	 * @brief Обработчик выхода из состояния
	 *
	 * @param object
	 */
	virtual void onExit() = 0;

	/**
	 * @brief Обработчик событий
	 *
	 * @param object
	 * @param event
	 */
	//virtual void onEvent(const Event& event) {}

	/**
	 * @brief Обновить логику
	 *
	 * @param object
	 */
	virtual void doLogic() = 0;

protected:
	Object * _object;
	int _type;
};

#endif // STATE_H
