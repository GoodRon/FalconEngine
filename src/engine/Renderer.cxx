/*
 * Copyright (c) 2014, Roman Meyta <theshrodingerscat@gmail.com>
 * All rights reserved
 */

#include <SDL2/SDL.h>

#include "Renderer.h"
#include "EngineException.h"

using namespace std;

Renderer::Renderer(int width, int height) :
	m_window(nullptr),
	m_renderer(nullptr),
	m_viewport( {0, 0, width, height}) {
	m_window = SDL_CreateWindow("Falcon Engine",
	                            SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
	                            m_viewport.w, m_viewport.h, SDL_WINDOW_SHOWN);

	if (m_window == nullptr) {
		throw EngineException(SDL_GetError());
	}

	m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED |
	                                SDL_RENDERER_PRESENTVSYNC);

	if (m_renderer == nullptr) {
		SDL_DestroyWindow(m_window);
		throw EngineException(SDL_GetError());
	}
}

Renderer::~Renderer() {
	if (m_renderer) {
		SDL_DestroyRenderer(m_renderer);
	}

	if (m_window) {
		SDL_DestroyWindow(m_window);
	}
}

bool Renderer::clear() {
	if (SDL_RenderClear(m_renderer) != 0) {
		return false;
	}

	return true;
}

bool Renderer::drawTexture(TexturePointer& texture, SDL_Rect* source,
                           SDL_Rect* destination) {
	if (!texture) {
		return false;
	}

	// TODO check if inside viewport

	if (SDL_RenderCopy(m_renderer, texture.get(), source, destination) != 0) {
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

	// WARNING check it!
	SDL_Texture* screen = SDL_GetRenderTarget(m_renderer);
	SDL_SetRenderTarget(m_renderer, destinationTexture.get());
	bool ret = drawTexture(sourceTexture, source, destination);
	SDL_SetRenderTarget(m_renderer, screen);
	return ret;
}

bool Renderer::clearTexture(TexturePointer& texture) {
	// WARNING check it!
	SDL_Texture* screen = SDL_GetRenderTarget(m_renderer);
	SDL_SetRenderTarget(m_renderer, texture.get());
	bool ret = clear();
	SDL_SetRenderTarget(m_renderer, screen);
	return ret;
}

SDL_Renderer* Renderer::getContext() const {
	return m_renderer;
}

SDL_Rect Renderer::getViewport() const {
	return m_viewport;
}

void Renderer::setViewport(const SDL_Rect& viewport) {
	// TODO resize
	m_viewport = viewport;
}
