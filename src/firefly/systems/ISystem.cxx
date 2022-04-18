#include "ISystem.h"

#include "Entity.h"
#include "components/IComponent.h"

namespace firefly {

ISystem::ISystem(const std::string& name, 
	Engine* engine): 
	_name(name), 
	_engine(engine),
	_requiredComponents(),
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

void ISystem::update() {
}

bool ISystem::checkComponents(Entity* entity) const {
	if (!entity) {
		return false;
	}

	IComponent* component = nullptr;

	for (auto& componentName: _requiredComponents) {
		component = entity->getComponent(
			getComponentId(componentName));
		if (!component) {
			return false;
		}
	}
	return true;
}

void ISystem::lockEntities() const {
}

void ISystem::unlockEntities() const {
}

}
