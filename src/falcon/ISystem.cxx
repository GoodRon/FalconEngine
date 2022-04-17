#include "ISystem.h"

#include "Entity.h"

namespace falcon {

ISystem::ISystem(const std::string& name): 
	_name(name), 
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
	if (_entities.find(id) != _entities.end()) {
		return false;
	}

	_entities[id] = entity;
	return true;
}

void ISystem::unregisterEntity(EntityID id) {
	_entities.erase(id);
}



}
