/*
 * Copyright (c) 2014, Roman Meyta <theshrodingerscat@gmail.com>
 * All rights reserved
 */

#include <thread>

#include <SDL2/SDL.h>

#include "Engine.h"
#include "TimerPool.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "ObjectManager.h"
#include "EngineException.h"

namespace falcon {

Engine::Engine(int width, int height) :
	_isRunning(true),
	_returnCode(0),
	_logicPeriod(10),
	_renderer(),
	_resourceManager(),
	_objectManager(),
	_timerPool(),
	_eventHandlers() {

	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		throw EngineException(SDL_GetError());
	}

	_renderer.reset(new Renderer(width, height));
	_resourceManager.reset(new ResourceManager(_renderer.get()));
	_objectManager.reset(new ObjectManager(_renderer.get()));
	_timerPool.reset(new TimerPool);
}

Engine::~Engine() {
	SDL_Quit();
}

/*
bool Engine::loadConfig(const std::string& file) {
	// TODO write me!
	return true;
}
*/

int Engine::execute() {

	_timerPool->addTimer(_logicPeriod.count(), [this](TimerPool::id_t) {
		if (!_objectManager) {
			return;
		}
		_objectManager->doObjectsLogic();
	});

	std::thread eventsThread([this](){
		SDL_Event event;
		while (_isRunning) {
			if (SDL_WaitEvent(&event) != 0) {
				onEvent(event);
			}
		}
	});

	while (_isRunning) {
		_timerPool->check();
//		SDL_Delay(10);

		_renderer->clearViewport();
		_objectManager->drawObjects();
		SDL_RenderPresent(_renderer->getContext());
	}
	eventsThread.join();
	return _returnCode;
}

Renderer* Engine::getRenderer() const {
	return _renderer.get();
}

ResourceManager* Engine::getResourceManager() const {
	return _resourceManager.get();
}

ObjectManager* Engine::getObjectManager() const {
	return _objectManager.get();
}

TimerPool* Engine::getTimersPool() const {
	return _timerPool.get();
}

void Engine::pushEventHandler(const eventHandler& handler) {
	_eventHandlers.push_back(handler);
}

void Engine::clearEventHandlers() {
	_eventHandlers.clear();
}

void Engine::onEvent(const SDL_Event& event) {
	switch (event.type) {
		case SDL_QUIT:
			_isRunning = false;
			break;
		case SDL_KEYDOWN:
			switch (event.key.keysym.sym) {
				case SDLK_ESCAPE:
					_isRunning = false;
					break;
				default:
					break;
			}
			break;
		default:
			break;
	}

	for (auto &handler: _eventHandlers) {
		handler(event);
	}
}

}
