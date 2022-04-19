/*
 * Copyright (c) 2022, Roman Meita <theshrodingerscat@gmail.com>
 * All rights reserved
 */

#ifndef FIREFLY_RENDERER_H
#define FIREFLY_RENDERER_H

#include <memory>

#include <SDL_rect.h>

struct SDL_Window;
struct SDL_Renderer;
struct SDL_Texture;

namespace firefly {

using TexturePointer = std::shared_ptr<SDL_Texture>;

class Renderer {
public:
	Renderer(int width, int heigh);

	~Renderer();

	Renderer(const Renderer& other) = delete;
	Renderer& operator=(Renderer& other) = delete;

	bool clearViewport();

	bool drawTexture(TexturePointer& texture, SDL_Rect* source = nullptr,
					 SDL_Rect* destination = nullptr);

	bool drawTexture(TexturePointer& texture, SDL_Rect* source,
					 SDL_Rect* destination, double angle, SDL_Point* center);

	bool drawTextureToTexture(TexturePointer& sourceTexture,
							  TexturePointer& destinationTexture,
							  SDL_Rect* source,
							  SDL_Rect* destination);

	bool clearTexture(TexturePointer& texture);

	SDL_Renderer* getContext() const;

	SDL_Rect getViewport() const;

	void setViewport(const SDL_Rect& viewport);

private:
	std::shared_ptr<SDL_Window> _window;
	std::shared_ptr<SDL_Renderer> _renderer;
	SDL_Rect _viewport;
};

}

#endif // FIREFLY_RENDERER_H
