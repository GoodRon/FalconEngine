/*
 * Copyright (c) 2014, Roman Meyta <theshrodingerscat@gmail.com>
 * All rights reserved
 */

#include <iostream>
#include <thread>

#include <SDL2/SDL.h>

#include "Engine.h"
#include "TimerPool.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "EngineException.h"
#include "ObjectManager.h"

using namespace std;

Engine::Engine(unsigned width, unsigned height) :
	m_run(true),
	m_returnCode(0),
	m_frameFrequency(33),
	m_logicFrequency(10),
	m_renderer(nullptr),
	m_resourceManager(nullptr),
	m_objectManager(nullptr),
	m_timers(new TimerPool),
	m_eventHandlers() {
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		throw EngineException(SDL_GetError());
	}

	m_renderer = new Renderer(width, height);
	m_resourceManager = new ResourceManager(m_renderer);
	m_objectManager = new ObjectManager(m_renderer);
}

Engine::Engine() :
	Engine(0, 0) {
}

Engine::~Engine() {
	delete m_objectManager;
	delete m_resourceManager;
	delete m_renderer;
	delete m_timers;
	SDL_Quit();
}

/*
bool Engine::loadConfig(const std::string& file) {
	// TODO write me!
	return true;
}
*/

int Engine::execute() {
	// TODO dynamic framerate
	m_timers->addTimer(m_frameFrequency, [this](TimerPool::id_t) {
		if (!m_renderer || !m_objectManager) {
			return;
		}
		m_renderer->clearViewport();
		m_objectManager->drawAllObjects();
		SDL_RenderPresent(m_renderer->getContext());
	});

	m_timers->addTimer(m_logicFrequency, [this](TimerPool::id_t) {
		if (!m_objectManager) {
			return;
		}
		m_objectManager->doObjectsLogic();
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
		SDL_Delay(10);
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

void Engine::pushEventHandler(const eventHandler& handler) {
	m_eventHandlers.push_back(handler);
}

void Engine::clearEventHandlers() {
	m_eventHandlers.clear();
}

void Engine::onEvent(const SDL_Event& event) {
	// Дефолтный обработчик
	switch (event.type) {
		case SDL_QUIT:
			m_run = false;
			break;
		case SDL_KEYDOWN:
			switch (event.key.keysym.sym) {
				case SDLK_ESCAPE:
					m_run = false;
					break;
				default:
					break;
			}
			break;
		default:
			break;
	}

	// Остальные обработчики
	for (auto &handler: m_eventHandlers) {
		handler(event);
	}
}
