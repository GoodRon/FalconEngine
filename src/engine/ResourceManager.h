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
class IAnimation;

/**
 * @brief Умный указатель на объект текстуры
 */
typedef std::shared_ptr<SDL_Texture> TexturePointer;

/**
 * @brief Текстурная карта. Двумерный массив текстур
 */
typedef std::vector<std::vector<TexturePointer>> TextureMap;

/**
 * @brief Умный указатель на объект анимации
 */
typedef std::shared_ptr<IAnimation> AnimationPointer;

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

	// TODO remove
	/**
	 * @brief Создать текстурную карту
	 *
	 * @param source исходная развертка
	 * @param rect размер одной текстуры
	 * @return TextureMap
	 */
	TextureMap createTextureMap(TexturePointer source, const SDL_Rect& rect) const;

	/**
	 * @brief Загрузка анимации по описанию из json-файла
	 *
	 * @param json путь к файлу описани
	 * @return AnimationPointer
	 */
	AnimationPointer loadAnimation(const std::string& json);

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

	/**
	 * @brief Мэп анимаций
	 */
	std::unordered_map<std::string, AnimationPointer> m_animations;
};

#endif // RESOURCEMANAGER_H
