/*
 * Copyright (c) 2022, Roman Meita <theshrodingerscat@gmail.com>
 * All rights reserved
 */

#ifndef FALCON_RESOURCE_MANAGER_H
#define FALCON_RESOURCE_MANAGER_H

#include <string>
#include <memory>
#include <vector>
#include <unordered_map>

struct SDL_Texture;

namespace falcon {

class Renderer;
class IAnimation;

using TexturePointer = std::shared_ptr<SDL_Texture>;
using AnimationPointer = std::shared_ptr<IAnimation>;

class ResourceManager {
public:
	ResourceManager(Renderer* renderer);
	~ResourceManager();

	ResourceManager(const ResourceManager&) = delete;
	ResourceManager& operator=(ResourceManager&) = delete;

	TexturePointer loadTexture(const std::string& name);


//	AnimationPointer loadAnimation(const std::string& json);

	void freeUnused();

private:
	Renderer* _renderer;
	std::unordered_map<std::string, TexturePointer> _textureCache;
};

}

#endif // FALCON_RESOURCE_MANAGER_H
