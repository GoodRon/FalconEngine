/*
 * Copyright (c) 2022, Roman Meita <theshrodingerscat@gmail.com>
 * All rights reserved
 */

#ifndef FIREFLY_SYSTEM_MANAGER_H
#define FIREFLY_SYSTEM_MANAGER_H

#include <string>
#include <unordered_map>
#include <memory>

#include "Types.h"

namespace firefly {

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

	bool onEvent(
		const std::shared_ptr<IEvent>& event) const;

	void clear();

private:
	std::unordered_map<std::string, std::shared_ptr<ISystem>> _systems;
};

}

#endif // FIREFLY_SYSTEM_MANAGER_H
