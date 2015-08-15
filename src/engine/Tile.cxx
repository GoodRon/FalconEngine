/*
 * Copyright (c) 2014, Roman Meyta <theshrodingerscat@gmail.com>
 * All rights reserved
 */

#include <SDL2/SDL.h>

#include "Tile.h"
#include "Renderer.h"

Tile::Tile(TexturePointer texture) :
	WorldObject(),
	m_texture(texture) {
	SDL_Rect profile = {0, 0, 0, 0};
	SDL_QueryTexture(m_texture.get(), nullptr, nullptr, &(profile.w), &(profile.h));
	m_width = profile.w;
	m_height = profile.h;
}

TexturePointer Tile::getTexture() const {
	return m_texture;
}

void Tile::draw(Renderer* renderer) {
	if (renderer == nullptr) {
		return;
	}

	if (!getVisibility()) {
		return;
	}

	auto profile = getPositionAndProfile();
	auto rdest = renderer->getViewport();
	profile.x += rdest.x;
	profile.y += rdest.y;
	renderer->clearViewport();
	renderer->drawTexture(m_texture, nullptr, &profile);
}
