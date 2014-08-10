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
	void pushObject(std::shared_ptr<WorldObject> object);

	/**
	 * @brief Обновить логику объектов
	 *
	 * @return void
	 */
	void doObjectsLogic(const std::chrono::milliseconds& timeDelta);

	/**
	 * @brief Отрисовать все объекты
	 *
	 * @return void
	 */
	void drawAllObjects();

private:
	/**
	 * @brief Отсортировать объекты по приоритету отрисовк
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
	std::vector<std::shared_ptr<WorldObject>> m_objects;
};

#endif // OBJECTMANAGER_H
