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
#include "Renderer.h"

using namespace std;

Engine::Engine() :
	m_width(1024),
	m_height(768),
	m_run(true),
	m_returnCode(0) {
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		cout << "SDL_Init Error: " << SDL_GetError() << endl;
	}
}

Engine::~Engine() {
	SDL_Quit();
}

bool Engine::loadConfig(const std::string& file) {

	return true;
}

int Engine::execute() {
	Renderer& renderer = Renderer::getInstance();
	renderer.init(m_width, m_height);

	TimerPool& timers = TimerPool::getInstance();
	timers.addTimer(33, [](TimerPool::id_t) {
		SDL_RenderPresent(Renderer::getInstance().get());
	});

	Texture_ptr background = ResourceManager::getInstance().loadTexture("background.png");
	timers.addTimer(33, [&background](TimerPool::id_t) {
		Renderer& renderer = Renderer::getInstance();
		SDL_Rect rsource = {0, 0, 0, 0};
		SDL_QueryTexture(background.get(), nullptr, nullptr, &(rsource.w), &(rsource.h));
		SDL_Rect rdest = renderer.getPosition();
		rsource.x += rdest.x;
		rsource.y += rdest.y;
		SDL_RenderClear(renderer.get());
		SDL_RenderCopy(renderer.get(), background.get(), nullptr, &rsource);
	});

	thread eventsThread([this](){
		SDL_Event event;
		while (m_run) {
			if (SDL_WaitEvent(&event) != 0) {
				onEvent(event);
			}
		}
	});

	while (m_run) {
		timers.check();
		usleep(1000);
	}
	eventsThread.join();
	return m_returnCode;
}

void Engine::onEvent(const SDL_Event& event) {
	switch (event.type) {
		case SDL_QUIT:
			m_run = false;
			break;
		case SDL_KEYDOWN:
			switch (event.key.keysym.sym) {
				case SDLK_ESCAPE:
					m_run = false;
					break;
				case SDLK_UP: {
					SDL_Rect rdest = Renderer::getInstance().getPosition();
					Renderer::getInstance().setPosition(rdest.x, rdest.y + 5);
				} break;
				case SDLK_DOWN: {
					SDL_Rect rdest = Renderer::getInstance().getPosition();
					Renderer::getInstance().setPosition(rdest.x, rdest.y - 5);
				} break;
				default:
					break;
			}
			break;
		default:
			break;
	}
}
