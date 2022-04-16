#include "ISystem.h"

namespace falcon {

ISystem::ISystem(const std::string& name): 
	_name(name), 
	_isReady(false),
	_entities() {
}
		
ISystem::~ISystem() {
}

const std::string ISystem::getName() const {
	return _name;
}

bool ISystem::isReady() const {
	return _isReady;
}

bool ISystem::registerEntity(IEntity* entity) {
	if (!entity) {
		return false;
	}

	if (!isReady()) {
		return false;
	}

	if (!checkComponents(entity)) {
		return false;
	}

	_entities.insert(entity);
	return true;
}

void ISystem::unregisterEntity(IEntity* entity) {
	if (!entity) {
		return;
	}

	_entities.erase(entity);
}

void ISystem::setReady(bool isReady) {
	_isReady = isReady;
}

}
