/*
 * Copyright (c) 2014, Roman Meyta <theshrodingerscat@gmail.com>
 * All rights reserved
 */

#include <SDL2/SDL.h>

#include "Tile.h"
#include "Renderer.h"

namespace falcon {

Tile::Tile(const TexturePointer& texture):
	WorldObject(),
	_texture(texture) {

	SDL_Rect profile = {0, 0, 0, 0};
	SDL_QueryTexture(_texture.get(), nullptr, nullptr, &(profile.w), &(profile.h));
	_width = profile.w;
	_height = profile.h;
}

Tile::~Tile() {
}

TexturePointer Tile::getTexture() const {
	return _texture;
}

void Tile::draw(Renderer* renderer) {
	if (!renderer) {
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
	renderer->drawTexture(_texture, nullptr, &profile);
}

}
