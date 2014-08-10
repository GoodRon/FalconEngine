/*
 * Copyright (c) 2014, Roman Meyta <theshrodingerscat@gmail.com>
 * All rights reserved
 */

#ifndef TILE_H
#define TILE_H

#include <memory>

struct SDL_Texture;
struct SDL_Rect;

/**
 * @brief Умный указатель на объект текстуры
 */
typedef std::shared_ptr<SDL_Texture> TexturePointer;

/**
 * @brief Класс тайла
 */
class Tile {
public:
	/**
	 * @brief Конструктор
	 *
	 * @param texture текстура
	 */
	Tile(TexturePointer& texture);

	/**
	 * @brief Вернуть текстуру тайла
	 *
	 * @return TexturePointer
	 */
	TexturePointer getTexture() const;

	/**
	 * @brief Задать позицию для тайла
	 *
	 * @param x
	 * @param y
	 * @return void
	 */
	void setPosition(int x, int y);

	/**
	 * @brief Вернуть мировые координаты и габариты текстуры
	 *
	 * @return SDL_Rect
	 */
	SDL_Rect getPositionAndProfile() const;

	/**
	 * @brief Установить видимость
	 *
	 * @param visible
	 * @return void
	 */
	void setVisible(bool visible);

	/**
	 * @brief Вернуть видимость
	 *
	 * @return bool
	 */
	bool isVisible() const;

private:
	/**
	 * @brief Текстура тайла
	 */
	TexturePointer m_texture;

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

	/**
	 * @brief ПРизнак видимости
	 */
	bool m_visible;
};

#endif // TILE_H
