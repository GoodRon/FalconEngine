/*
 * Copyright (c) 2014, Roman Meyta <theshrodingerscat@gmail.com>
 * All rights reserved
 */

#ifndef TILE_H
#define TILE_H

#include <memory>

#include <WorldObject.h>

struct SDL_Texture;
struct SDL_Rect;

/**
 * @brief Умный указатель на объект текстуры
 */
typedef std::shared_ptr<SDL_Texture> TexturePointer;

/**
 * @brief Класс тайла
 */
class Tile : public WorldObject {
public:
	/**
	 * @brief Конструктор
	 *
	 * @param texture текстура
	 */
	Tile(TexturePointer texture);

	/**
	 * @brief Вернуть текстуру тайла
	 *
	 * @return TexturePointer
	 */
	TexturePointer getTexture() const;

	/**
	 * @brief overload
	 */
	virtual void draw(Renderer* renderer);

private:
	/**
	 * @brief Текстура тайла
	 */
	TexturePointer m_texture;
};

#endif // TILE_H
