/*
 * Copyright (c) 2014, Roman Meyta <theshrodingerscat@gmail.com>
 * All rights reserved
 */

#ifndef STATEMANAGER_H
#define STATEMANAGER_H

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

	
};

 #endif // STATEMANAGER_H
