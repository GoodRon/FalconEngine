/*
 * Copyright (c) 2022, Roman Meita <theshrodingerscat@gmail.com>
 * All rights reserved
 */

#ifndef FIREFLY_ENGINE_H
#define FIREFLY_ENGINE_H

#include <SDL.h>

#include <vector>
#include <functional>
#include <memory>
#include <atomic>
#include <queue>
#include <mutex>

namespace firefly {

class Renderer;
class ResourceManager;
class EntityPrototypes;
class ObjectManager;
class SystemManager;
class EventManager;
class RenderingSystem;

class Engine {
public:
	Engine(int width, int height);
	~Engine();
	
	Engine(const Engine&) = delete;
	Engine& operator=(const Engine& other) = delete;

	int run();
	void stop();

	bool isRunning() const;

	Renderer* getRenderer() const;
	ResourceManager* getResourceManager() const;
	ObjectManager* getObjectManager() const;

	EntityPrototypes* getEntityPrototypes() const;
	
	SystemManager* getSystemManager() const;
	EventManager* getEventManager() const;

private:
	void onSDLEvent(const SDL_Event& event);

private:
	std::atomic<bool> _isRunning;
	int _returnCode;
	std::unique_ptr<Renderer> _renderer;
	std::unique_ptr<ResourceManager> _resourceManager;
	std::unique_ptr<ObjectManager> _objectManager;
	std::unique_ptr<EntityPrototypes> _entityPrototypes;
	std::unique_ptr<SystemManager> _systemManager;
	std::unique_ptr<EventManager> _eventManager;
	std::shared_ptr<firefly::RenderingSystem> _renderingSystem;
	std::mutex _eventMutex;
	std::queue<SDL_Event> _eventQueue;
	std::atomic<bool> _isEventAwaiting;
};

}

#endif // FIREFLY_ENGINE_H
