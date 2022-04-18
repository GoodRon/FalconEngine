/*
 * Copyright (c) 2022, Roman Meita <theshrodingerscat@gmail.com>
 * All rights reserved
 */

#ifndef FIREFLY_FRAME_H
#define FIREFLY_FRAME_H

#include <memory>

#include <SDL_rect.h>

struct SDL_Texture;

namespace firefly {

using TexturePointer = std::shared_ptr<SDL_Texture>;

class Frame {
public:
	Frame(const TexturePointer& texture, 
		  const SDL_Rect& sourceRect,
		  int durationMs = 0);
	~Frame();

	Frame(const Frame&) = default;
	Frame(Frame&&) = default;

	Frame& operator=(const Frame&) = default;
	Frame& operator=(Frame&&) = default;

	TexturePointer getTexture() const;
	SDL_Rect getSourceRect() const;
	int getDuration() const;

private:
	TexturePointer _texture;
	SDL_Rect _sourceRect;
	int _durationMs;
};

}

#endif // FIREFLY_FRAME_H
