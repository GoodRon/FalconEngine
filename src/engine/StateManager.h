/*
 * Copyright (c) 2014, Roman Meyta <theshrodingerscat@gmail.com>
 * All rights reserved
 */

#ifndef STATEMANAGER_H
#define STATEMANAGER_H

#include <stack>
#include <memory>

class State;

/**
 * @brief Менеджер состояний
 */
class StateManager {
public:
	/**
	 * @brief Вернуть ссылку на объект синглтона
	 * @return ResourceManager&
	 */
	static StateManager& getInstance() {
		static StateManager manager;
		return manager;
	}



private:
	/**
	 * @brief Конструктор
	 */
	StateManager();

	/**
	 * @brief Деструктор
	 */
	~StateManager();

	/**
	 * @brief Копирующий конструктор
	 * 
	 * @param other
	 */
	StateManager(const StateManager& other) = delete;

	/**
	 * @brief Оператор присваивания
	 * 
	 * @param other
	 */
	StateManager& operator=(StateManager& other) = delete;

private:
	/**
	 * @brief Стэк состояний
	 */
	std::stack<std::unique_ptr<State>> m_statesQueue;

	// TODO object manager
};

 #endif // STATEMANAGER_H
