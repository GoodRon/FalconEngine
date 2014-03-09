/*
 * Copyright (c) 2014, Roman Meyta <theshrodingerscat@gmail.com>
 * All rights reserved
 */

#include <iostream>
#include <thread>
#include <unistd.h>

#include <SDL2/SDL.h>

#include "Engine.h"
#include "TimerPool.h"
#include "ResourceManager.h"

using namespace std;

Engine::Engine() :
	m_width(1024),
	m_height(768),
	m_window(nullptr),
	m_renderer(nullptr),
	m_run(true),
	m_init(false),
	m_returnCode(0) {
}

bool Engine::loadConfig(const std::string& file) {

	return true;
}

int Engine::execute() {
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		cout << "SDL_Init Error: " << SDL_GetError() << endl;
		return 1;
	}

	m_window = SDL_CreateWindow("Falcon Engine",
								SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
								m_width, m_height, SDL_WINDOW_SHOWN);
	if (m_window == nullptr) {
		cerr << "Window creation failed: " << SDL_GetError() << endl;
		SDL_Quit();
		return 1;
	}

	m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED |
									SDL_RENDERER_PRESENTVSYNC);
	if (m_renderer == nullptr) {
		cerr << "Renderer Creation Failed: " << SDL_GetError() << endl;
		SDL_DestroyWindow(m_window);
		SDL_Quit();
		return 1;
	}

	m_init = true;

	Texture_ptr background = ResourceManager::getInstance().loadTexture(m_renderer, "background.png");

	TimerPool timers;
	timers.addTimer(100, [this, background](TimerPool::id_t) {
		SDL_Rect rsource = {0, 0, 0, 0};
		SDL_QueryTexture(background.get(), nullptr, nullptr, &(rsource.w), &(rsource.h));
		SDL_RenderClear(m_renderer);
		SDL_RenderCopy(m_renderer, background.get(), nullptr, &rsource);
		SDL_RenderPresent(m_renderer);
	});

	SDL_Event event;
	while (m_run) {
		if (SDL_WaitEvent(&event) != 0) {
			onEvent(event);
		}
		timers.check();
	}

	SDL_DestroyRenderer(m_renderer);
	SDL_DestroyWindow(m_window);
	SDL_Quit();
	return m_returnCode;
}

void Engine::onEvent(const SDL_Event& event) {
	switch (event.type) {
		case SDL_QUIT:
			m_run = false;
			break;
		case SDL_KEYDOWN:
			if (event.key.keysym.sym == SDLK_ESCAPE) {
				m_run = false;
			}
			break;
		default:
			break;
	}
}
