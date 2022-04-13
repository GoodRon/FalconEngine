/*
 * Copyright (c) 2014, Roman Meyta <theshrodingerscat@gmail.com>
 * All rights reserved
 */

#include <SDL.h>

#include "IsometricField.h"
#include "Tile.h"
#include "Renderer.h"

namespace falcon {

IsometricField::IsometricField(
	std::vector<std::vector<std::shared_ptr<Tile>>> tiles, 
	const SDL_Rect& tileSize) :
	WorldObject(),
	_tiles(tiles),
	_tileSize(tileSize) {
}

IsometricField::~IsometricField() {
}

SDL_Rect IsometricField::getProfile() const {
	SDL_Rect rect = {0, 0, 0, 0};

	if (_tiles.empty()) {
		return rect;
	}
	if (_tiles[0].empty()) {
		return rect;
	}

	SDL_Rect tileProfile = _tiles[0][0]->getProfile();
	rect.h = (_tiles.size() + _tiles[0].size()) * tileProfile.h / 2;
	rect.w = (_tiles.size() + _tiles[0].size()) * tileProfile.w / 2;

	return rect;
}

void IsometricField::draw(Renderer* renderer) {
	// TODO cache
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
	SDL_Rect tileDestination = {0, 0, _tileSize.w, _tileSize.h};

	if (_tiles.empty()) {
		return outTexture;
	}
	if (_tiles[0].empty()) {
		return outTexture;
	}

	outTexture.reset(SDL_CreateTexture(renderer->getContext(), SDL_PIXELFORMAT_RGBA8888,
                                       SDL_TEXTUREACCESS_TARGET, fieldProfile.w, fieldProfile.h),
	                 SDL_DestroyTexture);

	renderer->clearTexture(outTexture);

	// TODO check!
	for (unsigned i = 0; i < _tiles.size(); ++i) {
		for (unsigned j = 0; j < _tiles[i].size(); ++j) {
			// TODO recalculate!
			tileDestination = _tiles[i][j]->getProfile();
			tileDestination.x = (fieldProfile.w - _tiles.size() * _tileSize.w / 2 - _tileSize.w / 2) 
							  	+ (_tileSize.w / 2) * i - (_tileSize.w / 2) * j;
			tileDestination.y = _tileSize.h - tileDestination.h + (_tileSize.h / 2) * i 
								+ (_tileSize.h / 2) * j;
			TexturePointer tileTexture = _tiles[i][j]->getTexture();
			renderer->drawTextureToTexture(tileTexture, outTexture,
			                               nullptr, &tileDestination);
		}
	}

	return outTexture;
}

}
