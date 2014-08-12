/*
 * Copyright (c) 2014, Roman Meyta <theshrodingerscat@gmail.com>
 * All rights reserved
 */

#include <SDL2/SDL.h>

#include "Field.h"
#include "Tile.h"
#include "Renderer.h"

Field::Field(std::vector<std::vector<std::shared_ptr<Tile>>> tiles) :
	WorldObject(),
	m_tiles(tiles) {
}

Field::~Field() {
}

SDL_Rect Field::getProfile() const {
	SDL_Rect rect = {0, 0, 0, 0};

	if (m_tiles.empty()) {
		return rect;
	}
	if (m_tiles[0].empty()) {
		return rect;
	}

	SDL_Rect tileProfile = m_tiles[0][0]->getProfile();
	rect.h = m_tiles.size() * tileProfile.h;
	rect.w = m_tiles[0].size() * tileProfile.w;

	return rect;
}

void Field::draw(Renderer* renderer) {
	// TODO кэширование
	SDL_Rect source = getProfile();
	SDL_Rect destination = getPositionAndProfile();
	TexturePointer fieldTexture = createFieldTexture(renderer);
	renderer->drawTexture(fieldTexture, &source, &destination);
}

int Field::getDrawPriority() {
	// TODO write
	return 0;
}

TexturePointer Field::createFieldTexture(Renderer* renderer) {
	TexturePointer outTexture;
    SDL_Rect fieldProfile = getProfile();
	SDL_Rect tileProfile = {0, 0, 0, 0}; // NOTE предполагаем одинаковые тайлы
	SDL_Rect tileDestination = {0, 0, 0, 0};

	if (m_tiles.empty()) {
		return outTexture;
	}
	if (m_tiles[0].empty()) {
		return outTexture;
	}

	tileProfile = m_tiles[0][0]->getProfile();
	tileDestination = m_tiles[0][0]->getPositionAndProfile();

	outTexture.reset(SDL_CreateTexture(renderer->getContext(), SDL_PIXELFORMAT_RGBA8888,
                                       SDL_TEXTUREACCESS_TARGET, fieldProfile.w, fieldProfile.h),
	                 SDL_DestroyTexture);

	// TODO check!
	for (unsigned i = 0; i < m_tiles.size(); ++i) {
		for (unsigned j = 0; j < m_tiles[i].size(); ++j) {
			tileDestination.x = tileProfile.w * j;
			tileDestination.y = tileProfile.h * i;
			TexturePointer tileTexture = m_tiles[i][j]->getTexture();
			renderer->drawTextureToTexture(tileTexture, outTexture,
			                               &tileProfile, &tileDestination);
		}
	}

	return outTexture;
}
