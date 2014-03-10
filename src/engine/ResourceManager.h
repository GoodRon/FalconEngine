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

typedef std::shared_ptr<SDL_Texture> Texture_ptr;

class ResourceManager {
public:
	static ResourceManager& getInstance() {
		static ResourceManager manager;
		return manager;
	}

	Texture_ptr loadTexture(const std::string& name);

private:
	ResourceManager();
	~ResourceManager();

	ResourceManager(const ResourceManager& other) = delete;
	ResourceManager& operator=(ResourceManager& other) = delete;

private:
	std::unordered_map<std::string, Texture_ptr> m_textures;
};

#endif // RESOURCEMANAGER_H
