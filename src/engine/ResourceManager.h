/*
 * Copyright (c) 2014, Roman Meyta <theshrodingerscat@gmail.com>
 * All rights reserved
 */

#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include <string>
#include <memory>

struct SDL_Texture;

typedef std::shared_ptr<SDL_Texture> Texture_ptr;

class ResourceManager {
public:
	static ResourceManager& getInstance() {
		static ResourceManager manager;
		return manager;
	}

	Texture_ptr loadTexture(const std::string& file) const;

private:
	ResourceManager();
	~ResourceManager();

	ResourceManager(const ResourceManager& other) = delete;
	ResourceManager& operator=(ResourceManager& other) = delete;
};

#endif // RESOURCEMANAGER_H
