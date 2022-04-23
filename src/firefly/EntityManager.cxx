/*
 * Copyright (c) 2022, Roman Meita <theshrodingerscat@gmail.com>
 * All rights reserved
 */

#include "EntityManager.h"

#include "Entity.h"
#include "EventManager.h"

#include "events\EntityEvent.h"

namespace firefly {

EntityManager::EntityManager(EventManager* eventManager):
	_eventManager(eventManager) {
}

EntityManager::~EntityManager() {
}

bool EntityManager::addEntity(
	const std::shared_ptr<Entity>& entity) {

	if (!entity) {
		return false;
	}

	const auto id = entity->getId();
	if (hasEntity(id)) {
		return true;
	}

	_entites[id] = entity;

	std::shared_ptr<IEvent> event(new EntityEvent(entity));
	_eventManager->registerEvent(std::move(event));
	return true;
}

void EntityManager::removeEntity(EntityID id) {
	if (!hasEntity(id)) {
		return;
	}

	std::shared_ptr<IEvent> event(new EntityEvent(_entites[id], true));
	_eventManager->registerEvent(std::move(event));

	_entites.erase(id);
}

bool EntityManager::hasEntity(EntityID id) const {
	if (_entites.find(id) != _entites.end()) {
		return true;
	}
	return false;
}

std::shared_ptr<Entity> 
EntityManager::getEntity(EntityID id) {
	if (!hasEntity(id)) {
		return nullptr;
	}
	return _entites[id];
}

void EntityManager::clear() {
	_entites.clear();
}

}
