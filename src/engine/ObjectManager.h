/*
 * Copyright (c) 2014, Roman Meyta <theshrodingerscat@gmail.com>
 * All rights reserved
 */

#ifndef OBJECTMANAGER_H
#define OBJECTMANAGER_H

#include <vector>
#include <memory>
#include <chrono>

class WorldObject;
class Renderer;

/**
 * @brief Умный указатель на мировой объект
 */
typedef std::shared_ptr<WorldObject> WorldObjectPointer;

/**
 * @brief Менеджер мировых объектов
 */
class ObjectManager {
public:
	/**
	 * @brief Конструктор
	 *
	 * @param renderer указатель на объект рендерера
	 */
	ObjectManager(Renderer* renderer);

	/**
	 * @brief Деструктор
	 */
	~ObjectManager();

	/**
	 * @brief Добавить объект
	 *
	 * @param object
	 * @return void
	 */
	void pushObject(const WorldObjectPointer& object);

	/**
	 * @brief Обновить логику объектов
	 *
	 * @return void
	 */
	void doObjectsLogic();

	/**
	 * @brief Отрисовать все объекты
	 *
	 * @return void
	 */
	void drawAllObjects();

	/**
	 * @brief Вернуть объект по экранным координатам
	 * @param x
	 * @param y
	 *
	 * @return WorldObjectPointer
	 */
	WorldObjectPointer getObjectByCoordinates(int x, int y);

	/**
	 * @brief Вернуть объект по идентификатору
	 * @param id
	 *
	 * @return WorldObjectPointer
	 */
	WorldObjectPointer getObjectById(int id);

	// void sendEvent();

	/**
	 * @brief Сбросить все объекты
	 *
	 * @return void
	 */
	void clear();

private:
	/**
	 * @brief Отсортировать объекты по приоритету отрисовки
	 *
	 * @return void
	 */
	void sortByDrawPriority();

	/**
	 * @brief Копирующий конструктор
	 *
	 * @param other
	 */
	ObjectManager(const ObjectManager& other) = delete;

	/**
	 * @brief Оператор присваивания
	 *
	 * @param other
	 */
	ObjectManager& operator=(ObjectManager& other) = delete;

private:
	/**
	 * @brief Указатель на объект рендерера
	 */
	Renderer* m_renderer;

	/**
	 * @brief Все объекты
	 */
	std::vector<WorldObjectPointer> m_objects;
};

#endif // OBJECTMANAGER_H
