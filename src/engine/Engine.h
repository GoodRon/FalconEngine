/*
 * Copyright (c) 2014, Roman Meyta <theshrodingerscat@gmail.com>
 * All rights reserved
 */

#ifndef ENGINE_H
#define ENGINE_H

#include <string>

union SDL_Event;
class Renderer;
class ResourceManager;
class TimerPool;
class ObjectManager;

/**
 * @brief Класс игрового движка
 */
class Engine {
public:
	/**
	 * @brief Конструктор
	 */
	Engine();

	/**
	 * @brief Деструктор
	 */
	~Engine();

	/**
	 * @brief Обработка конфигурационного файла
	 *
	 * @param file путь к файлу
	 * @return bool
	 */
	bool loadConfig(const std::string& file);

	/**
	 * @brief Основной рабочий цикл
	 *
	 * @return int
	 */
	int execute();

	/**
	 * @brief Вернуть указатель на рендерер
	 *
	 * @return Renderer*
	 */
	Renderer* getRenderer() const;

	/**
	 * @brief Вернуть указатель на менеджер ресурсов
	 *
	 * @return ResourceManager*
	 */
	ResourceManager* getResourceManager() const;

	/**
	 * @brief Вернуть указатель на менеджер объектов
	 *
	 * @return ObjectManager*
	 */
	ObjectManager* getObjectManager() const;

	/**
	 * @brief Вернуть указатель на пул таймеров
	 *
	 * @return TimerPool*
	 */
	TimerPool* getTimersPool() const;

private:
	/**
	 * @brief Обработчик событий
	 *
	 * @param event
	 */
	void onEvent(const SDL_Event& event);

private:
	/**
	 * @brief Флаг работы движка
	 */
	bool m_run;

	/**
	 * @brief Возвращаемое значение
	 */
	int m_returnCode;

	/**
	 * @brief Рендерер
	 */
	Renderer* m_renderer;

	/**
	 * @brief Менеджер ресурсов
	 */
	ResourceManager* m_resourceManager;

	/**
	 * @brief Менеджер объектов
	 */
	ObjectManager* m_objectManager;

	/**
	 * @brief Пул таймеров
	 */
	TimerPool* m_timers;
};

#endif // ENGINE_H
