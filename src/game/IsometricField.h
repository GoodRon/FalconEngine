/*
 * Copyright (c) 2014, Roman Meyta <theshrodingerscat@gmail.com>
 * All rights reserved
 */

#ifndef FIELD_H
#define FIELD_H

#include <vector>
#include <memory>
#include <string>

#include "WorldObject.h"

class Tile;
struct SDL_Texture;
struct SDL_Rect;

/**
 * @brief Умный указатель на объект текстуры
 */
typedef std::shared_ptr<SDL_Texture> TexturePointer;

/**
 * @brief Класс игрового поля
 */
class IsometricField : public WorldObject {
public:
    // NOTE кэшировать карту, перерисовывать только изменённые тайлы
    
	/**
	 * @brief Конструктор из двумерного массива (сделать трехмерный и свойства тайлов)
	 *
	 * @param tiles массив тайлов
	 * @param tileSize размер тайла
	 */
	IsometricField(std::vector<std::vector<std::shared_ptr<Tile>>> tiles, 
				   const SDL_Rect& tileSize);

	/**
	 * @brief Конструктор из json
	 *
	 * @param jsonFile путь к json
	 */
	// IsometricField(const std::string& jsonFile);

	/**
	 * @override
	 */
	virtual ~IsometricField();
    
    /**
     * @override
     */
    virtual SDL_Rect getProfile() const;
    
	/**
	 * @override
	 */
	virtual void draw(Renderer* renderer);

	/**
	 * @override
	 */
	virtual int getDrawPriority();

private:
    /**
     * @brief Создать текстуру поля
     * 
     * @return TexturePointer
     */
    TexturePointer createFieldTexture(Renderer* renderer);

private:
	/**
	 * @brief Карта тайлов
	 */
	std::vector<std::vector<std::shared_ptr<Tile>>> m_tiles;

	/**
	 * @brief Размер тайла на карте (без учета смещения по высоте)
	 */
	SDL_Rect m_tileSize;
};

#endif // FIELD_H
