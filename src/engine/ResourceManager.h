/*
 * Copyright (c) 2014, Roman Meyta <theshrodingerscat@gmail.com>
 * All rights reserved
 */

#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include <string>
#include <memory>
#include <unordered_map>

struct SDL_Texture;
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

	//std::vector<TexturePointer> loadTextureVector();

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
