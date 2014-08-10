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
#include "EngineException.h"
#include "ObjectManager.h"

using namespace std;

Engine::Engine() :
	m_run(true),
	m_returnCode(0),
	m_renderer(nullptr),
	m_resourceManager(nullptr),
	m_objectManager(nullptr),
	m_timers(new TimerPool) {
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		throw EngineException(SDL_GetError());
	}

	m_renderer = new Renderer(1024, 768);
	m_resourceManager = new ResourceManager(m_renderer);
    m_objectManager = new ObjectManager(m_renderer);
}

Engine::~Engine() {
	delete m_resourceManager;
	delete m_renderer;
	delete m_timers;

	SDL_Quit();
}

bool Engine::loadConfig(const std::string& file) {
	// TODO write me!
	return true;
}

int Engine::execute() {
	// TODO write better
	m_timers->addTimer(33, [this](TimerPool::id_t) {
		SDL_RenderPresent(m_renderer->getContext());
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
		m_timers->check();
        // TODO write better
		usleep(1000);
	}
	eventsThread.join();
	return m_returnCode;
}

Renderer* Engine::getRenderer() const {
	return m_renderer;
}

ResourceManager* Engine::getResourceManager() const {
    return m_resourceManager;
}

ObjectManager* Engine::getObjectManager() const {
	return m_objectManager;
}

TimerPool* Engine::getTimersPool() const {
	return m_timers;
}

void Engine::onEvent(const SDL_Event& event) {
	// TODO just debug. write better
	switch (event.type) {
		case SDL_QUIT:
			m_run = false;
			break;
		case SDL_KEYDOWN:
			switch (event.key.keysym.sym) {
				case SDLK_ESCAPE:
					m_run = false;
					break;
				case SDLK_UP:
					if (m_renderer) {
						SDL_Rect rdest = m_renderer->getViewport();
						rdest.y += 5;
						m_renderer->setViewport(rdest);
					}
					break;
				case SDLK_DOWN:
					if (m_renderer) {
						SDL_Rect rdest = m_renderer->getViewport();
						rdest.y -= 5;
						m_renderer->setViewport(rdest);
					}
					break;
				default:
					break;
			}
			break;
		default:
			break;
	}
}
