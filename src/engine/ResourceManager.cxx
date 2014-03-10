/*
 * Copyright (c) 2014, Roman Meyta <theshrodingerscat@gmail.com>
 * All rights reserved
 */

#include <iostream>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "ResourceManager.h"
#include "Renderer.h"

using namespace std;

ResourceManager::ResourceManager() {
}

ResourceManager::~ResourceManager() {
}

Texture_ptr ResourceManager::loadTexture(const string& name) {
	if (m_textures.find(name) != m_textures.end()) {
		return m_textures.at(name);
	}

	Texture_ptr ptr;
	Renderer& renderer = Renderer::getInstance();

	if (!renderer.isInit()) {
		return ptr;
	}

	SDL_Surface* surface = IMG_Load(name.c_str());
	if (surface == nullptr) {
		cerr << "Unable to load image " << name << ". Error: " << IMG_GetError() << endl;
		return ptr;
	}

	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer.get(), surface);
	if (texture == nullptr) {
		cerr << "Unable to create texture from image " << name << ". Error: " << SDL_GetError() << endl;
		SDL_FreeSurface(surface);
		return ptr;
	}

	SDL_FreeSurface(surface);
	ptr.reset(texture, SDL_DestroyTexture);
	m_textures.emplace(name, ptr);
	return ptr;
}
