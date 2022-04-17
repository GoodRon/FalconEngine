/*
 * Copyright (c) 2022, Roman Meita <theshrodingerscat@gmail.com>
 * All rights reserved
 */

#ifndef FALCON_ENTITY_MANAGER_H
#define FALCON_ENTITY_MANAGER_H

#include <memory>
#include <unordered_map>

namespace falcon {

using EntityID = int;

class IEntity;

// NOTE do we need this?
class EntityManager {
public:
	EntityManager();
	~EntityManager();

	EntityManager(const EntityManager&) = delete;
	EntityManager& operator=(const EntityManager&) = delete;

	template<class T, class... ARGS>
	std::shared_ptr<T> createEntity(ARGS&&... args) {
		std::shared_ptr<T> entity(new T(std::forward<ARGS>(args)...));

		EntityID id = getNextId();

		entity->setId(id);
		_entities[id] = entity;
		return entity;
	}

	// TODO remove?
	EntityID registerEntity(const std::shared_ptr<IEntity>& entity);
	void unregisterEntity(EntityID id);

	std::shared_ptr<IEntity> getEntity(EntityID id);

	void clear();

private:
	EntityID getNextId();

private:
	EntityID _nextId;
	std::unordered_map<EntityID, std::shared_ptr<IEntity>> _entities;
};

}

#endif // FALCON_ENTITY_MANAGER_H
