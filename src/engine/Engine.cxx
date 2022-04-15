/*
 * Copyright (c) 2022, Roman Meita <theshrodingerscat@gmail.com>
 * All rights reserved
 */

#include <thread>

#include <SDL.h>

#include "Engine.h"
#include "TimerPool.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "ObjectManager.h"
#include "EngineException.h"

namespace falcon {

constexpr size_t maxQueuedEvents = 1024;

Engine::Engine(int width, int height):
	_isRunning(true),
	_returnCode(0),
	_renderer(),
	_resourceManager(),
	_objectManager(),
	_timerPool(),
	_eventHandlers(),
	_handlersMutex(),
	_eventQueue(),
	_eventMutex(),
	_isEventReceived(false) {

	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		throw EngineException(SDL_GetError());
	}

	_renderer.reset(new Renderer(width, height));
	_resourceManager.reset(new ResourceManager(_renderer.get()));
	_objectManager.reset(new ObjectManager(_renderer.get()));
	_timerPool.reset(new TimerPool);

	_timerPool->addTimer(10, [this](TimerPool::id_t) {
		if (!_objectManager) {
			return;
		}
		_objectManager->updateAll();
	});
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

int Engine::run() {
	
	std::thread logicThread([this](){
		// TODO use accurate timers here

		const Uint32 delayMs = 5;
		std::queue<SDL_Event> events;

		while (_isRunning) {

			_timerPool->check();

			if (_isEventReceived) {
				std::lock_guard<std::mutex> locker(_eventMutex);
				events.swap(_eventQueue);
				_isEventReceived = false;
			}

			while (!events.empty()) {
				onEvent(events.front());
				events.pop();
			}

			// TODO calculate delay instead of using the constant value
			SDL_Delay(delayMs);
		}
	});
	
	SDL_Event event;

	// TODO make an option for restricting fps
	while (_isRunning) {
		_renderer->clearViewport();
		_objectManager->drawAll();
		SDL_RenderPresent(_renderer->getContext());
		
		std::lock_guard<std::mutex> locker(_eventMutex);
		while (SDL_PollEvent(&event) != 0) {
			if (_eventQueue.size() >= maxQueuedEvents) {
				_eventQueue.pop();
			}

			_eventQueue.push(std::move(event));
		}

		if (!_isEventReceived && !_eventQueue.empty()) {
			_isEventReceived = true;
		}
	}
	logicThread.join();
	return _returnCode;
}

void Engine::stop() {
	_isRunning = false;
}
	
bool Engine::isRunning() const {
	return _isRunning;
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

void Engine::pushEventHandler(const EventHandler& handler) {
	std::lock_guard<std::mutex> locker(_handlersMutex);
	_eventHandlers.push_back(handler);
}

void Engine::clearEventHandlers() {
	std::lock_guard<std::mutex> locker(_handlersMutex);
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

	// TODO remove the locking here
	std::lock_guard<std::mutex> locker(_handlersMutex);
	for (auto &handler: _eventHandlers) {
		if (handler(event)) {
			break;
		}
	}
}

}
