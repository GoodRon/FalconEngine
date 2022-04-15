/*
 * Copyright (c) 2022, Roman Meita <theshrodingerscat@gmail.com>
 * All rights reserved
 */

#include "Renderer.h"
#include "EngineException.h"

#include <SDL.h>

namespace falcon {

Renderer::Renderer(int width, int height) :
	_window(nullptr),
	_renderer(nullptr),
	_viewport({0, 0, width, height}) {

	// TODO pass the header string here
	auto window = SDL_CreateWindow("Falcon Engine",
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		_viewport.w, _viewport.h, SDL_WINDOW_SHOWN);

	if (window == nullptr) {
		throw EngineException(SDL_GetError());
	}

	_window.reset(window, SDL_DestroyWindow);

	auto renderer = SDL_CreateRenderer(_window.get(), -1, 
		SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	if (renderer == nullptr) {
		_window.reset();
		throw EngineException(SDL_GetError());
	}
	_renderer.reset(renderer, SDL_DestroyRenderer);
}

Renderer::~Renderer() {
	_renderer.reset();
	_window.reset();
}

bool Renderer::clearViewport() {
	if (SDL_RenderClear(_renderer.get()) != 0) {
		return false;
	}
	return true;
}

bool Renderer::drawTexture(TexturePointer& texture, SDL_Rect* source,
						   SDL_Rect* destination) {
	if (!texture) {
		return false;
	}

	// TODO check if texture is inside the viewport

	if (SDL_RenderCopy(_renderer.get(), texture.get(), source, destination) != 0) {
		return false;
	}
	return true;
}

bool Renderer::drawTextureToTexture(TexturePointer& sourceTexture,
									TexturePointer& destinationTexture,
									SDL_Rect* source,
									SDL_Rect* destination) {
	if ((!sourceTexture) || (!destinationTexture)) {
		return false;
	}

	SDL_Texture* screen = SDL_GetRenderTarget(_renderer.get());
	SDL_SetRenderTarget(_renderer.get(), destinationTexture.get());
	bool ret = drawTexture(sourceTexture, source, destination);
	SDL_SetRenderTarget(_renderer.get(), screen);
	return ret;
}

bool Renderer::clearTexture(TexturePointer& texture) {
	SDL_Texture* screen = SDL_GetRenderTarget(_renderer.get());
	SDL_SetRenderTarget(_renderer.get(), texture.get());
	bool ret = clearViewport();
	SDL_SetRenderTarget(_renderer.get(), screen);
	return ret;
}

SDL_Renderer* Renderer::getContext() const {
	return _renderer.get();
}

SDL_Rect Renderer::getViewport() const {
	return _viewport;
}

void Renderer::setViewport(const SDL_Rect& viewport) {
	// TODO resize
	_viewport = viewport;
}

}
