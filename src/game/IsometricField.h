/*
 * Copyright (c) 2014, Roman Meyta <theshrodingerscat@gmail.com>
 * All rights reserved
 */

#ifndef FALCON_FIELD_H
#define FALCON_FIELD_H

#include <vector>
#include <memory>

#include "WorldObject.h"

struct SDL_Texture;
struct SDL_Rect;

namespace falcon {

class Tile;

using TexturePointer = std::shared_ptr<SDL_Texture>;

class IsometricField : public WorldObject {
public:
	IsometricField(std::vector<std::vector<std::shared_ptr<Tile>>> tiles, 
				   const SDL_Rect& tileSize);

	virtual ~IsometricField();

	virtual SDL_Rect getProfile() const;

	virtual void draw(Renderer* renderer);

	virtual int getDrawPriority();

private:
	TexturePointer createFieldTexture(Renderer* renderer);

private:
	std::vector<std::vector<std::shared_ptr<Tile>>> _tiles;
	SDL_Rect _tileSize;
};

}

#endif // FALCON_FIELD_H
