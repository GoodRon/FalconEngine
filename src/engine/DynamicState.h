/*
 * Copyright (c) 2014, Roman Meyta <theshrodingerscat@gmail.com>
 * All rights reserved
 */

#ifndef DYNAMIC_STATE_H
#define DYNAMIC_STATE_H

#include <string>
#include <functional>

#include "State.h"

struct SDL_Event;

/**
 * @brief Динамический класс состояния
 */
template <class Object>
class DynamicState : public State<Object> {
public:
	/**
	 * @brief Функция-обработчик
	 */
	typedef std::function<void (Object* object)> CommonHandler;

	/**
	 * @brief Функция-обработчик событий типа SDL_Event
	 */
	typedef std::function<void (Object* object, const SDL_Event& event)> EventHandler;

	/**
	 * @brief Конструктор
	 *
	 * @param name
	 * @param onEnter
	 * @param doLogic
	 * @param onEvent
	 * @param onExit
	 */
	DynamicState(const std::string& name,
		  		 const State::CommonHandler& onEnter,
		  		 const State::CommonHandler& doLogic,
		  		 const State::EventHandler& onEvent,
		  		 const State::CommonHandler& onExit) : State<Object>(name), 
													   m_onEnter(onEnter),
													   m_doLogic(doLogic),
													   m_onEvent(onEvent),
													   m_onExit(onExit) {}

	/**
	 * @brief Деструктор
	 */
	virtual ~DynamicState() {}

	/**
	 * @brief Обработчик входа в состояние
	 * 
	 * @param object
	 */
	virtual void onEnter(Object* object) {
		if (!m_onEnter) {
			return;
		}
		m_onEnter(object);
	}

	/**
	 * @brief Обновить логику
	 * 
	 * @param object
	 */
	virtual void doLogic(Object* object) {
		if (!m_doLogic) {
			return;
		}
		m_doLogic(object);
	}


	/**
	 * @brief Обработчик событий
	 * 
	 * @param object
	 * @param event
	 */
	virtual void onEvent(Object* object, const SDL_Event& event) {
		if (!m_onEvent) {
			return;
		}
		m_onEvent(object, event);
	}

	/**
	 * @brief Обработчик выхода из состояния
	 * 
	 * @param object
	 */
	virtual void onExit(Object* object) {
		if (!m_onExit) {
			return;
		}
		m_onExit(object);
	}

private:
	/**
	 * @brief Обработчик входа в состояние
	 */
	CommonHandler m_onEnter;

	/**
	 * @brief Обработчик обновления логики
	 */
	CommonHandler m_doLogic;

	/**
	 * @brief Обработчик событий
	 */
	EventHandler m_onEvent;

	/**
	 * @brief Обработчик выхода из состояния
	 */
	CommonHandler m_onExit;
};

#endif // DYNAMIC_STATE_H
