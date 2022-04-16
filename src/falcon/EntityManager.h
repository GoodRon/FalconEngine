/*
 * Copyright (c) 2022, Roman Meita <theshrodingerscat@gmail.com>
 * All rights reserved
 */

#ifndef FALCON_ENTITY_MANAGER_H
#define FALCON_ENTITY_MANAGER_H

#include <unordered_map>

namespace falcon {

using EntityID = int;

class EntityManager {
public:
	EntityManager();
	~EntityManager();

	EntityManager(const EntityManager&) = delete;
	EntityManager& operator=(const EntityManager&) = delete;

	EntityID createEntity();
	void destroyEntity(EntityID id);

	void clear();

private:
	std::unordered_map<EntityID, bool> _entities;
};

}

#endif // FALCON_ENTITY_MANAGER_H
