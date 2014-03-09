/*
 * Copyright (c) 2014, Roman Meyta <theshrodingerscat@gmail.com>
 * All rights reserved
 */

#include <SDL2/SDL.h>

#include "Renderer.h"

Renderer::Renderer() :
	m_window(nullptr),
	m_renderer(nullptr),
	m_x(0),
	m_y(0),
	m_width(0),
	m_height(0),
	m_isInit(false) {
}

Renderer::~Renderer() {
	if (m_renderer) {
		SDL_DestroyRenderer(m_renderer);
	}
	if (m_window) {
		SDL_DestroyWindow(m_window);
	}
}

bool Renderer::init(int width, int height) {
	if (m_isInit) {
		return m_isInit;
	}
	m_width = width;
	m_height = height;

	m_window = SDL_CreateWindow("Falcon Engine",
								SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
								m_width, m_height, SDL_WINDOW_SHOWN);
	if (m_window == nullptr) {
//		cerr << "Window creation failed: " << SDL_GetError() << endl;
		return m_isInit;
	}

	m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED |
									SDL_RENDERER_PRESENTVSYNC);
	if (m_renderer == nullptr) {
//		cerr << "Renderer Creation Failed: " << SDL_GetError() << endl;
		SDL_DestroyWindow(m_window);
		return m_isInit;
	}
	m_isInit = true;
	return m_isInit;
}


bool Renderer::isInit() const {
	return m_isInit;
}

SDL_Renderer* Renderer::get() const {
	return m_renderer;
}

SDL_Rect Renderer::getPosition() const {
	SDL_Rect rect = {m_x, m_y, m_width, m_height};
	return rect;
}

void Renderer::setPosition(int x, int y) {
	m_x = x;
	m_y = y;
}
