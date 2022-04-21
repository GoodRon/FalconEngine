/*
 * Copyright (c) 2022, Roman Meita <theshrodingerscat@gmail.com>
 * All rights reserved
 */

#ifndef FIREFLY_OBJECT_MANAGER_H
#define FIREFLY_OBJECT_MANAGER_H

#include <vector>
#include <unordered_map>
#include <memory>

#include "Types.h"

namespace firefly {

class Entity;
class SystemManager;

class EntityManager {
public:
	EntityManager(SystemManager* systemManager);
	~EntityManager();

	EntityManager(const EntityManager&) = delete;
	EntityManager& operator=(EntityManager&) = delete;

	bool addEntity(const std::shared_ptr<Entity>& entity);
	void removeEntity(EntityID id);

	void clear();

private:
	SystemManager* const _systemManager;
	std::unordered_map<EntityID, std::shared_ptr<Entity>> _entites;
};

}

#endif // FIREFLY_OBJECT_MANAGER_H
