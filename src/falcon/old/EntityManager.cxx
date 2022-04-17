#include "EntityManager.h"

#include "IEntity.h"

namespace falcon {

EntityManager::EntityManager():
	_nextId(0),
	_entities() {
}

EntityManager::~EntityManager() {
}

EntityID EntityManager::registerEntity(const std::shared_ptr<IEntity>& entity) {
	if (!entity) {
		return -1;
	}

	if (entity->getId() < 0) {
		entity->setId(_nextId++);
	}

	const auto id = entity->getId();

	if (getEntity(id) == nullptr) {
		_entities[id] = entity;
	}
	return id;
}

void EntityManager::unregisterEntity(EntityID id) {
	_entities.erase(id);
}

std::shared_ptr<IEntity> EntityManager::getEntity(EntityID id) {
	if (_entities.find(id) == _entities.end()) {
		return nullptr;
	}

	return _entities[id];
}

void EntityManager::clear() {
	_entities.clear();
}

EntityID EntityManager::getNextId() {
	return _nextId++;
}

}
