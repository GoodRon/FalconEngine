/*
 * Copyright (c) 2014, Roman Meyta <theshrodingerscat@gmail.com>
 * All rights reserved
 */

#ifndef WORLDOBJECT_H
#define WORLDOBJECT_H

#include <chrono>

struct SDL_Rect;
class Renderer;

/**
 * @brief Объект в мире
 */
class WorldObject {
public:
	/**
	 * @brief Конструктор
	 */
	WorldObject();

	/**
	 * @brief Конструктор
	 * @param x
	 * @param y
	 */
	WorldObject(int x, int y);

	/**
	 * @brief Деструктор
	 */
	virtual ~WorldObject() = 0;

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
	 * @brief Работа внутренней логики объекта
	 *
	 * @param timeDelta прошедшее время с момента последнего вызова (мс)
	 * @return void
	 */
	virtual void doLogic(const std::chrono::milliseconds& timeDelta);

	// cacheFullState();

	// TODO maybe this shoud be done in different way
	/**
	 * @brief Вернуть приоритет при отрисовке
	 *
	 * @return int значение приоритета (меньше - выше)
	 */
	virtual int getDrawPriority();

protected:
	/**
	 * @brief Координата x
	 */
	int m_x;

	/**
	 * @brief Координата y
	 */
	int m_y;

	/**
	 * @brief Ширина
	 */
	int m_width;

	/**
	 * @brief Высота
	 */
	int m_height;
};

#endif // WORLDOBJECT_H
