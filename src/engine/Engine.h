/*
 * Copyright (c) 2022, Roman Meita <theshrodingerscat@gmail.com>
 * All rights reserved
 */

#ifndef FALCON_ENGINE_H
#define FALCON_ENGINE_H

#include <vector>
#include <functional>
#include <memory>
#include <atomic>
#include <queue>
#include <mutex>

union SDL_Event;

namespace falcon {

class Renderer;
class ResourceManager;
class TimerPool;
class ObjectManager;

using EventHandler = std::function<bool(const SDL_Event&)>;

class Engine {
public:
	Engine(int width, int height);
	~Engine();

	Engine(const Engine&) = delete;
	Engine& operator=(const Engine& other) = delete;

	// bool loadConfig(const std::string& file);

	int run();
	void stop();

	bool isRunning() const;

	Renderer* getRenderer() const;
	ResourceManager* getResourceManager() const;
	ObjectManager* getObjectManager() const;
	TimerPool* getTimersPool() const;

	// TODO remove from here?
	void pushEventHandler(const EventHandler& handler);

	void clearEventHandlers();

private:
	void onEvent(const SDL_Event& event);

private:
	std::atomic<bool> _isRunning;
	int _returnCode;
	std::unique_ptr<Renderer> _renderer;
	std::unique_ptr<ResourceManager> _resourceManager;
	std::unique_ptr<ObjectManager> _objectManager;
	std::unique_ptr<TimerPool> _timerPool;
	std::vector<EventHandler> _eventHandlers;
	std::mutex _handlersMutex;
	std::queue<SDL_Event> _eventQueue;
	std::mutex _eventMutex;
	std::atomic<bool> _isEventReceived;
};

}

#endif // FALCON_ENGINE_H
