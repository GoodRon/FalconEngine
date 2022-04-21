/*
 * Copyright (c) 2022, Roman Meita <theshrodingerscat@gmail.com>
 * All rights reserved
 */

#include "EntityManager.h"

#include "Entity.h"
#include "SystemManager.h"

namespace firefly {

EntityManager::EntityManager(SystemManager* systemManager):
	_systemManager(systemManager),
	_entites() {
}

EntityManager::~EntityManager() {
}

bool EntityManager::addEntity(
	const std::shared_ptr<Entity>& entity) {

	if (!entity) {
		return false;
	}

	const auto id = entity->getId();
	if (_entites.find(id) != _entites.end()) {
		return true;
	}

	_entites[id] = entity;

	_systemManager->registerEntity(entity.get());
	return true;
}

void EntityManager::removeEntity(EntityID id) {
	auto it = _entites.find(id);
	if (it == _entites.end()) {
		return;
	}

	_systemManager->unregisterEntity((*it).second->getId());
	_entites.erase(id);
}

void EntityManager::clear() {
	_entites.clear();
}

}
