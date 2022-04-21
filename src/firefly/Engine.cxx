/*
 * Copyright (c) 2022, Roman Meita <theshrodingerscat@gmail.com>
 * All rights reserved
 */

#include <SDL_timer.h>

#include <thread>

#include "Engine.h"
#include "Entity.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "EntityManager.h"
#include "EngineException.h"
#include "SystemManager.h"
#include "EventManager.h"
#include "EntityPrototypes.h"

#include "systems/RenderingSystem.h"
#include "events/NativeEvent.h"
#include "components/IComponent.h"

namespace firefly {

constexpr size_t maxQueuedEvents = 1024;

Engine::Engine(int width, int height):
	_isRunning(true),
	_returnCode(0),
	_renderer(),
	_resourceManager(),
	_entityManager(),
	_entityPrototypes(),
	_systemManager(),
	_eventManager(),
	_renderingSystem(),
	_eventMutex(),
	_eventQueue(),
	_isEventAwaiting(false) {

	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		throw EngineException(SDL_GetError());
	}

	_systemManager.reset(new SystemManager());

	_renderer.reset(new Renderer(width, height));
	_resourceManager.reset(new ResourceManager(_renderer.get()));
	_entityManager.reset(new EntityManager(_systemManager.get()));
	_entityPrototypes.reset(new EntityPrototypes);

	_eventManager.reset(new EventManager(_systemManager.get()));

	_renderingSystem.reset(
		new firefly::RenderingSystem(this));
	_systemManager->addSystem(_renderingSystem);
}

Engine::~Engine() {
	SDL_Quit();
}

void Engine::setWindowHeader(const std::string& header) {
	_renderer->setWindowHeader(header);
}

void Engine::setWindowIcon(const std::string& iconPath) {
	_renderer->setWindowIcon(iconPath);
}

int Engine::run() {

	std::thread logicThread([this](){
		// TODO set the logic period
		constexpr uint64_t logicPeriodMs = 16;
		uint64_t elapsedMs = 0;
		uint64_t timepoint = 0;

		std::queue<SDL_Event> events;

		while (_isRunning) {
			timepoint = SDL_GetTicks64();

			_systemManager->update();

			if (_isEventAwaiting) {
				std::lock_guard<std::mutex> locker(_eventMutex);
				events.swap(_eventQueue);
				_isEventAwaiting = false;
			}

			while (!events.empty()) {
				onSDLEvent(events.front());
				events.pop();
			}

			elapsedMs = SDL_GetTicks64() - timepoint;
			if (elapsedMs > logicPeriodMs) {
				continue;
			}

			SDL_Delay(logicPeriodMs - elapsedMs);
		}
	});
	
	SDL_Event event;

	// TODO make an option for restricting fps
	while (_isRunning) {
		_renderer->clearViewport();
		_renderingSystem->drawEntites();
		SDL_RenderPresent(_renderer->getContext());
		
		std::lock_guard<std::mutex> locker(_eventMutex);
		while (SDL_PollEvent(&event) != 0) {
			if (_eventQueue.size() >= maxQueuedEvents) {
				_eventQueue.pop();
			}

			_eventQueue.push(std::move(event));
		}

		if (!_isEventAwaiting && !_eventQueue.empty()) {
			_isEventAwaiting = true;
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

EntityManager* Engine::getEntityManager() const {
	return _entityManager.get();
}

EntityPrototypes* Engine::getEntityPrototypes() const {
	return _entityPrototypes.get();
}

SystemManager* Engine::getSystemManager() const {
	return _systemManager.get();
}

void Engine::onSDLEvent(const SDL_Event& event) {
	switch (event.type) {
		case SDL_QUIT:
			_isRunning = false;
			break;
		default:
			break;
	}

	std::shared_ptr<IEvent> nativeEvent(new NativeEvent(event));
	_eventManager->sendEvent(nativeEvent);
}

}
