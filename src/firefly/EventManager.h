/*
 * Copyright (c) 2022, Roman Meita <theshrodingerscat@gmail.com>
 * All rights reserved
 */

#ifndef FIREFLY_EVENT_MANAGER_H
#define FIREFLY_EVENT_MANAGER_H

#include <memory>
#include <queue>

namespace firefly {

class IEvent;
class SystemManager;

class EventManager {
public:
	EventManager(SystemManager* systemManager);
	~EventManager();

	EventManager(const EventManager&) = delete;
	EventManager& operator=(const EventManager&) = delete;

	void sendEvent(const std::shared_ptr<IEvent>& event) const;

private:
	SystemManager* const _systemManager;
};

}

#endif // FIREFLY_EVENT_MANAGER_H
 