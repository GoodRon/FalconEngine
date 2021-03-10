/*
 * Copyright (c) 2014, Roman Meyta <theshrodingerscat@gmail.com>
 * All rights reserved
 */

#ifndef FALCON_ENGINE_H
#define FALCON_ENGINE_H

#include <vector>
#include <functional>
#include <memory>
#include <chrono>

union SDL_Event;

namespace falcon {

class Renderer;
class ResourceManager;
class TimerPool;
class ObjectManager;

class Engine {
public:
	using eventHandler = std::function<void(const SDL_Event&)>;

	Engine(int width, int height);
	
	~Engine();

	Engine(const Engine&) = delete;
	Engine& operator=(const Engine& other) = delete;

	// bool loadConfig(const std::string& file);

	int execute();

	Renderer* getRenderer() const;
	ResourceManager* getResourceManager() const;
	ObjectManager* getObjectManager() const;
	TimerPool* getTimersPool() const;

	void pushEventHandler(const eventHandler& handler);

	void clearEventHandlers();

private:
	void onEvent(const SDL_Event& event);

private:
	bool _isRunning;
	int _returnCode;
	std::chrono::milliseconds _logicPeriod;
	std::unique_ptr<Renderer> _renderer;
	std::unique_ptr<ResourceManager> _resourceManager;
	std::unique_ptr<ObjectManager> _objectManager;
	std::unique_ptr<TimerPool> _timerPool;
	std::vector<eventHandler> _eventHandlers;
};

}

#endif // FALCON_ENGINE_H
