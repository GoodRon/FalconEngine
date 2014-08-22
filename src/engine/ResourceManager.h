/*
 * Copyright (c) 2014, Roman Meyta <theshrodingerscat@gmail.com>
 * All rights reserved
 */

#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include <string>
#include <memory>
#include <vector>
#include <unordered_map>

struct SDL_Texture;
struct SDL_Rect;
class Renderer;

/**
 * @brief Умный указатель на объект текстуры
 */
typedef std::shared_ptr<SDL_Texture> TexturePointer;

/**
 * @brief Менеджер ресурсов
 */
class ResourceManager {
public:
	/**
	 * @brief Конструктор
	 *
	 * @param renderer указатель на объект рендерера
	 */
	ResourceManager(Renderer* renderer);

	/**
	 * @brief Деструктор
	 */
	~ResourceManager();

	/**
	 * @brief Загрузка текстуры
	 *
	 * @param name имя текстуры
	 * @return TexturePointer
	 */
	TexturePointer loadTexture(const std::string& name);

	/**
	 * @brief Разделить текстуру на вектор текстур
	 * Текстуры вырезаются в порядке слева направо, rect задает размеры текстур в векторе.
	 * Вызов функции работает с одной строкой (относительно размеров rect) исходной текстуры 
	 * (если строк в ней несколько)
	 *
	 * @param source исходная текстура
	 * @param rect размер текстуры в векторе
	 * @param row строка в текстуре
	 * @return std::vector<TexturePointer>
	 */
	std::vector<TexturePointer> createTextureVector(TexturePointer source, const SDL_Rect& rect, 
												   	unsigned row = 0) const;

	/**
	 * @brief Освободить неиспользуемые текстуры
	 */
	void freeUnused();

private:
	/**
	 * @brief Копирующий конструктор
	 *
	 * @param other
	 */
	ResourceManager(const ResourceManager& other) = delete;

	/**
	 * @brief Оператор присваивания
	 *
	 * @param other
	 */
	ResourceManager& operator=(ResourceManager& other) = delete;

private:
	/**
	 * @brief Указатель на объект рендерера
	 */
	Renderer* m_renderer;

	/**
	 * @brief Мэп текстур
	 */
	std::unordered_map<std::string, TexturePointer> m_textures;
};

#endif // RESOURCEMANAGER_H
