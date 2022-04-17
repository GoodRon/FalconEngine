/*
 * Copyright (c) 2022, Roman Meita <theshrodingerscat@gmail.com>
 * All rights reserved
 */

#ifndef FALCON_ENGINE_H
#define FALCON_ENGINE_H

#include <SDL.h>

#include <vector>
#include <functional>
#include <memory>
#include <atomic>
#include <queue>
#include <mutex>

namespace falcon {

class Renderer;
class ResourceManager;
class TimerPool;
class ObjectManager;
class ComponentRegistry;
class SystemManager;
class EventManager;

using EventHandler = std::function<bool(const SDL_Event&)>;

class Engine {
public:
	static Engine& instance() {
		static Engine engine;
		return engine;
	}

	~Engine();

	// bool loadConfig(const std::string& file);

	bool initialize(int width, int height);
	bool isInitialized() const;

	int run();
	void stop();

	bool isRunning() const;

	Renderer* getRenderer() const;
	ResourceManager* getResourceManager() const;
	ObjectManager* getObjectManager() const;
	
	ComponentRegistry* getComponentRegistry() const;
	SystemManager* getSystemManager() const;

	EventManager* getEventManager() const;

	TimerPool* getTimersPool() const;

	// TODO remove from here?
	void pushEventHandler(const EventHandler& handler);

	void clearEventHandlers();

private:
	Engine();
	
	Engine(const Engine&) = delete;
	Engine& operator=(const Engine& other) = delete;

	void onEvent(const SDL_Event& event);

private:
	std::atomic<bool> _isInitialized;
	std::atomic<bool> _isRunning;
	int _returnCode;
	std::unique_ptr<Renderer> _renderer;
	std::unique_ptr<ResourceManager> _resourceManager;
	std::unique_ptr<ObjectManager> _objectManager;
	std::unique_ptr<ComponentRegistry> _componentRegistry;
	std::unique_ptr<SystemManager> _systemManager;
	std::unique_ptr<EventManager> _eventManager;
	std::unique_ptr<TimerPool> _timerPool;
	std::vector<EventHandler> _eventHandlers;
	std::mutex _handlersMutex;
	std::queue<SDL_Event> _eventQueue;
	std::mutex _eventMutex;
	std::atomic<bool> _isEventReceived;
};

}

#endif // FALCON_ENGINE_H
