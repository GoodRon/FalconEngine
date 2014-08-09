/*
 * Copyright (c) 2014, Roman Meyta <theshrodingerscat@gmail.com>
 * All rights reserved
 */

#ifndef WORLDOBJECT_H
#define WORLDOBJECT_H

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
    virtual ~WorldObject() = delete;
    
    /**
     * @brief Изменить позицию в мире
     * 
     * @param x
     * @param y
     * @return void
     */
    virtual void setPosition(int x, int y);
    
    /**
     * @brief Вернуть мировые координаты и габариты объекта
     * 
     * @return SDL_Rect
     */
    virtual SDL_Rect getPositionAndProfile() const;
    
    /**
     * @brief Отрисовать объект
     * 
     * @param renderer указатель на рендерер
     */
    virtual void drow(Renderer* renderer) = delete;
    
    // cacheFullState();
    
private:
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
