/*
 * Copyright (c) 2014, Roman Meyta <theshrodingerscat@gmail.com>
 * All rights reserved
 */

#include <SDL2/SDL.h>

#include "IsometricField.h"
#include "Tile.h"
#include "Renderer.h"

IsometricField::IsometricField(std::vector<std::vector<std::shared_ptr<Tile>>> tiles, 
							   const SDL_Rect& tileSize) :
	WorldObject(),
	m_tiles(tiles),
	m_tileSize(tileSize) {
}

/*
IsometricField::IsometricField(const std::string& jsonFile) {
	// TODO write me!
}
*/

IsometricField::~IsometricField() {
}

SDL_Rect IsometricField::getProfile() const {
	SDL_Rect rect = {0, 0, 0, 0};

	if (m_tiles.empty()) {
		return rect;
	}
	if (m_tiles[0].empty()) {
		return rect;
	}

	SDL_Rect tileProfile = m_tiles[0][0]->getProfile();
	rect.h = (m_tiles.size() + m_tiles[0].size()) * tileProfile.h / 2;
	rect.w = (m_tiles.size() + m_tiles[0].size()) * tileProfile.w / 2;

	return rect;
}

void IsometricField::draw(Renderer* renderer) {
	// TODO кэширование
	SDL_Rect source = getProfile();
	SDL_Rect destination = getPositionAndProfile();
	TexturePointer fieldTexture = createFieldTexture(renderer);
	renderer->drawTexture(fieldTexture, &source, &destination);
}

int IsometricField::getDrawPriority() {
	// TODO write
	return 0;
}

TexturePointer IsometricField::createFieldTexture(Renderer* renderer) {
	TexturePointer outTexture;
    SDL_Rect fieldProfile = getProfile();
	SDL_Rect tileDestination = {0, 0, m_tileSize.w, m_tileSize.h};

	if (m_tiles.empty()) {
		return outTexture;
	}
	if (m_tiles[0].empty()) {
		return outTexture;
	}

	outTexture.reset(SDL_CreateTexture(renderer->getContext(), SDL_PIXELFORMAT_RGBA8888,
                                       SDL_TEXTUREACCESS_TARGET, fieldProfile.w, fieldProfile.h),
	                 SDL_DestroyTexture);

	renderer->clearTexture(outTexture);

	// TODO check!
	for (unsigned i = 0; i < m_tiles.size(); ++i) {
		for (unsigned j = 0; j < m_tiles[i].size(); ++j) {
			// TODO recalculate!
			tileDestination = m_tiles[i][j]->getProfile();
			tileDestination.x = (fieldProfile.w - m_tiles.size() * m_tileSize.w / 2 - m_tileSize.w / 2) 
							  + (m_tileSize.w / 2) * i - (m_tileSize.w / 2) * j;
			tileDestination.y = m_tileSize.h - tileDestination.h + (m_tileSize.h / 2) * i 
								+ (m_tileSize.h / 2) * j;
			TexturePointer tileTexture = m_tiles[i][j]->getTexture();
			renderer->drawTextureToTexture(tileTexture, outTexture,
			                               nullptr, &tileDestination);
		}
	}

	return outTexture;
}
