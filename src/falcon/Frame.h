/*
 * Copyright (c) 2022, Roman Meita <theshrodingerscat@gmail.com>
 * All rights reserved
 */

#ifndef FALCON_FRAME_H
#define FALCON_FRAME_H

#include <memory>

#include <SDL_rect.h>

struct SDL_Texture;

namespace falcon {

using TexturePointer = std::shared_ptr<SDL_Texture>;

class Frame {
public:
	Frame(const TexturePointer& texture, 
		  const SDL_Rect& sourceRect);
	~Frame();

	Frame(const Frame&) = default;
	Frame(Frame&&) = default;

	Frame& operator=(const Frame&) = default;
	Frame& operator=(Frame&&) = default;

	TexturePointer getTexture() const;

	SDL_Rect getSourceRect() const;

	void setDurationMs(int durationMs);
	int getDuration() const;

private:
	TexturePointer _texture;
	SDL_Rect _sourceRect;
	int _durationMs;
};

}

#endif // FALCON_FRAME_H
