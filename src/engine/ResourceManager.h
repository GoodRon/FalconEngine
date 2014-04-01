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

typedef std::shared_ptr<SDL_Texture> TexturePointer;

/**
 * @brief Менеджер ресурсов
 */
class ResourceManager {
public:
	/**
	 * @brief Вернуть ссылку на объект синглтона
	 * @return ResourceManager&
	 */
	static ResourceManager& getInstance() {
		static ResourceManager manager;
		return manager;
	}

	/**
	 * @brief Загрузка текстуры
	 * 
	 * @param name имя текстуры
	 * @return TexturePointer
	 */
	TexturePointer loadTexture(const std::string& name);

	/**
	 * @brief Освободить неиспользуемые текстуры
	 */
	void freeUnused();

private:
	/**
	 * @brief Конструктор
	 */
	ResourceManager();

	/**
	 * @brief Деструктор
	 */
	~ResourceManager();

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
	 * @brief Мэп текстур
	 */
	std::unordered_map<std::string, TexturePointer> m_textures;
};

#endif // RESOURCEMANAGER_H
