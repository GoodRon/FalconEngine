/*
 * Copyright (c) 2014, Roman Meyta <theshrodingerscat@gmail.com>
 * All rights reserved
 */

#ifndef FALCON_TILE_H
#define FALCON_TILE_H

#include <memory>

#include "WorldObject.h"

struct SDL_Texture;
struct SDL_Rect;

namespace falcon {

using TexturePointer = std::shared_ptr<SDL_Texture>;

class Tile: public WorldObject {
public:
	Tile(const TexturePointer& texture);

	~Tile() override;

	TexturePointer getTexture() const;

	void draw(Renderer* renderer) override;

private:
	TexturePointer _texture;
};

}

#endif // FALCON_TILE_H
