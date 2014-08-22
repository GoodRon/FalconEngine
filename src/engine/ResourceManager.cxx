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

ResourceManager::ResourceManager(Renderer* renderer) : 
m_renderer(renderer) {
}

ResourceManager::~ResourceManager() {
}

TexturePointer ResourceManager::loadTexture(const string& name) {
	if (m_textures.find(name) != m_textures.end()) {
		return m_textures.at(name);
	}

	TexturePointer ptr;
	if (!m_renderer) {
		return ptr;
	}

	SDL_Surface* surface = IMG_Load(name.c_str());
	if (surface == nullptr) {
		cerr << "Unable to load image " << name << ". Error: " << IMG_GetError() 
			 << endl;
		return ptr;
	}

	SDL_Texture* texture = SDL_CreateTextureFromSurface(m_renderer->getContext(), 
														surface);
	if (texture == nullptr) {
		cerr << "Unable to create texture from image " << name << ". Error: " 
			 << SDL_GetError() << endl;
		SDL_FreeSurface(surface);
		return ptr;
	}

	SDL_FreeSurface(surface);
	ptr.reset(texture, SDL_DestroyTexture);
	m_textures.emplace(name, ptr);
	return ptr;
}

vector<TexturePointer> ResourceManager::createTextureVector(TexturePointer source, 
															const SDL_Rect& rect, 
										   					unsigned row) const {
	vector<TexturePointer> textures;

	if ((!m_renderer) || (!source) || (rect.w <= 0) || (rect.h <= 0)) {
		return textures;
	}

	Uint32 format;
	int access;
	int width;
	int height;

	SDL_QueryTexture(source.get(), &format, &access, &width, &height);

	unsigned cols = width / rect.w;
	unsigned rows = height / rect.h;

	if ((rows == 0) || (cols == 0) || (row >= rows)) {
		return textures;
	}

	for (unsigned col = 0; col < cols; ++col) {
		TexturePointer texture(SDL_CreateTexture(m_renderer->getContext(), 
							   format, SDL_TEXTUREACCESS_TARGET, rect.w, rect.h), 
							   SDL_DestroyTexture);
		SDL_Rect crop = {static_cast<int>(col * rect.w), static_cast<int>(row * rect.h), 
						 rect.w, rect.h};
		m_renderer->drawTextureToTexture(source, texture, &crop, nullptr);
		textures.push_back(texture);
	}
	return textures;
}

void ResourceManager::freeUnused() {
	for (auto texture = m_textures.begin(); texture != m_textures.end(); ++texture) {
		if ((*texture).second.use_count() <= 1) {
			m_textures.erase(texture);
		}
	}
}