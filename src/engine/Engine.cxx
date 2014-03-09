#include <iostream>
#include <unistd.h>

#include <SDL2/SDL.h>

#include "Engine.h"
#include "TimerPool.h"

using namespace std;

Engine::Engine() :
	m_width(1024),
	m_height(768),
	m_run(true),
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

	SDL_Window* window = SDL_CreateWindow("Falcon Engine",
										  SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
										  m_width, m_height, SDL_WINDOW_SHOWN);
	if (window == nullptr) {
		cerr << "Window creation failed: " << SDL_GetError() << endl;
		SDL_Quit();
		return 1;
	}

	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (renderer == nullptr) {
		cerr << "Renderer Creation Failed: " << SDL_GetError() << endl;
		SDL_DestroyWindow(window);
		SDL_Quit();
		return 1;
	}

	TimerPool timers;
	timers.addTimer(100, [renderer](TimerPool::id_t) {
		SDL_RenderPresent(renderer);
	});

	SDL_Event event;
	while (m_run) {
		if (SDL_PollEvent(&event) != 0) {
			onEvent(event);
		}
		timers.check();
	}

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return m_returnCode;
}

void Engine::onEvent(const SDL_Event& event) {
	switch (event.type) {
		case SDL_QUIT:
			m_run = false;
			break;
		default:
			break;
	}
}
