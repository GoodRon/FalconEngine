#include "ISystem.h"

#include "Entity.h"

namespace falcon {

ISystem::ISystem(const std::string& name, 
	Engine* engine): 
	_name(name), 
	_engine(engine),
	_entities() {
}
		
ISystem::~ISystem() {
}

const std::string ISystem::getName() const {
	return _name;
}

bool ISystem::registerEntity(Entity* entity) {
	if (!entity) {
		return false;
	}

	if (!checkComponents(entity)) {
		return false;
	}

	auto id = entity->getId();

	lockEntities();
	if (_entities.find(id) == _entities.end()) {
		_entities[id] = entity;
	}
	unlockEntities();
	return true;
}

void ISystem::unregisterEntity(EntityID id) {
	lockEntities();
	_entities.erase(id);
	unlockEntities();
}

void ISystem::lockEntities() const {
}

void ISystem::unlockEntities() const {
}

}
