/*
 * Copyright (c) 2014, Roman Meyta <theshrodingerscat@gmail.com>
 * All rights reserved
 */

#ifndef ENGINE_H
#define ENGINE_H

#include <string>
#include <vector>
#include <functional>

union SDL_Event;
class Renderer;
class ResourceManager;
class TimerPool;
class ObjectManager;

namespace engine {

class WorldBuilder;

/**
 * @brief Класс игрового движка
 */
class Engine {
public:
	/**
	 * @brief Описатель обработчика событий
	 */
	typedef std::function<void(const SDL_Event&)> eventHandler;

	/**
	 * @brief Конструктор
	 *
	 * @param width ширина порта вывода
	 * @param height выоста порта вывода
	 */
	Engine(unsigned width, unsigned height);

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
	// bool loadConfig(const std::string& file);

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

	WorldBuilder* getWorldBuilder() const;

	/**
	 * @brief Вернуть указатель на пул таймеров
	 *
	 * @return TimerPool*
	 */
	TimerPool* getTimersPool() const;

	/**
	 * @brief Добавить обработчик событий в стек
	 *
	 * @param handler
	 * @return void
	 */
	void pushEventHandler(const eventHandler& handler);

	/**
	 * @brief Очистить стек обработчиков событий
	 *
	 * @return void
	 */
	void clearEventHandlers();

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
	 * @brief Частота обновления кадров
	 */
	uint32_t m_frameFrequency;

	/**
	 * @brief Частота обновления логики
	 */
	uint32_t m_logicFrequency;

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

	WorldBuilder* m_worldBuilder;

	/**
	 * @brief Пул таймеров
	 */
	TimerPool* m_timers;

	/**
	 * @brief Стек обработчиков событий
	 */
	std::vector<eventHandler> m_eventHandlers;
};

}

#endif // ENGINE_H
