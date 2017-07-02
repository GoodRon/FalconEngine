/*
 * Copyright (c) 2014, Roman Meyta <theshrodingerscat@gmail.com>
 * All rights reserved
 */

#ifndef WORLDOBJECT_H
#define WORLDOBJECT_H

#include <chrono>

struct SDL_Rect;
class Renderer;
class Command;

/**
 * @brief Объект в мире
 */
class WorldObject {
public:
	/**
	 * @brief Конструктор
	 * @param x
	 * @param y
	 */
	WorldObject(int x, int y);

	/**
	 * @brief Конструктор
	 */
	WorldObject();

	/**
	 * @brief Деструктор
	 */
	virtual ~WorldObject() = 0;

	/**
	 * @brief Вернуть идентификатор объекта
	 *
	 * @return int персональный идентификатор
	 */
	int getId() const;

	/**
	 * @brief Изменить позицию в мире
	 *
	 * @param x
	 * @param y
	 * @return void
	 */
	virtual void setPosition(int x, int y);

	/**
	 * @brief Вернуть мировые координаты и габариты объекта в двумерной проекции
	 *
	 * @return SDL_Rect
	 */
	virtual SDL_Rect getPositionAndProfile() const;

	/**
	 * @brief Вернуть только габариты объекта в двумерной проекции
	 *
	 * @return SDL_Rect
	 */
	virtual SDL_Rect getProfile() const;

	/**
	 * @brief Вернуть только мировые координаты
	 *
	 * @return SDL_Rect
	 */
	virtual SDL_Rect getPosition() const;

	/**
	 * @brief Отрисовать объект
	 *
	 * @param renderer указатель на рендерер
	 */
	virtual void draw(Renderer* renderer) = 0;

	/**
	 * @brief Выполнить комманду
	 *
	 * @param command
	 */
	//virtual void executeCommand(Command* command);

	/**
	 * @brief Работа внутренней логики объекта
	 */
	virtual void doLogic();

	// cacheFullState();

	// isCollide();

	// TODO maybe this shoud be done in different way
	/**
	 * @brief Вернуть приоритет при отрисовке
	 *
	 * @return int значение приоритета (меньше - выше)
	 */
	virtual int getDrawPriority();

	/**
	 * @brief Установить признак видимости
	 *
	 * @param isVisible
	 */
	void setVisibility(bool isVisible);

	/**
	 * @brief Вернуть признак видимости
	 *
	 * @return bool
	 */
	bool isVisible() const;

	void setCollidability(bool isCollidable);

	bool isCollidable() const;

protected:
	/**
	 * @brief Идентификатор объекта
	 */
	int _id;

	/**
	 * @brief Координата x
	 */
	int _x;

	/**
	 * @brief Координата y
	 */
	int _y;

	/**
	 * @brief Ширина
	 */
	int _width;

	/**
	 * @brief Высота
	 */
	int _height;

	/**
	 * @brief Признак видимости
	 */
	bool _isVisible;

	bool _isCollidable;
};

#endif // WORLDOBJECT_H
