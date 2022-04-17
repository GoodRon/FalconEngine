/*
 * Copyright (c) 2022, Roman Meita <theshrodingerscat@gmail.com>
 * All rights reserved
 */

#ifndef FALCON_SYSTEM_MANAGER_H
#define FALCON_SYSTEM_MANAGER_H

#include <string>
#include <unordered_map>
#include <memory>

#include "Types.h"

namespace falcon {

class ISystem;
class IEvent;
class Entity;

class SystemManager {
public:
	SystemManager();
	~SystemManager();

	SystemManager(const SystemManager&) = delete;
	SystemManager& operator=(const SystemManager&) = delete;

	void addSystem(const std::shared_ptr<ISystem>& system);

	bool hasSystem(const std::string& name) const;

	void registerEntity(Entity* entity);
	void unregisterEntity(EntityID id);

	// NOTE remove?
	bool onEvent(
		const std::shared_ptr<IEvent>& event) const;

	void clear();

private:
	std::unordered_map<std::string, std::shared_ptr<ISystem>> _systems;
};

}

#endif // FALCON_SYSTEM_MANAGER_H
