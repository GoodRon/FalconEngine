/*
 * Copyright (c) 2014, Roman Meyta <theshrodingerscat@gmail.com>
 * All rights reserved
 */

#include <iostream>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "ResourceManager.h"

using namespace std;

ResourceManager::ResourceManager() {
}

ResourceManager::~ResourceManager() {
}

shared_ptr<SDL_Texture> ResourceManager::loadTexture(SDL_Renderer* renderer, const string& file) const {
	shared_ptr<SDL_Texture> ptr;

	if (renderer == nullptr) {
		return ptr;
	}

	SDL_Surface* surface = IMG_Load(file.c_str());
	if (surface == nullptr) {
		cerr << "Unable to load image " << file << ". Error: " << IMG_GetError() << endl;
		return ptr;
	}

	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
	if (texture == nullptr) {
		cerr << "Unable to create texture from image " << file << ". Error: " << SDL_GetError() << endl;
		SDL_FreeSurface(surface);
		return ptr;
	}

	SDL_FreeSurface(surface);
	ptr.reset(texture, SDL_DestroyTexture);
	return ptr;
}
