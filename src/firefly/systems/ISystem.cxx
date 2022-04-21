#include "ISystem.h"

#include <SDL_timer.h>

#include "Entity.h"
#include "components/IComponent.h"

namespace firefly {

ISystem::ISystem(const std::string& name, 
	Engine* engine): 
	_name(name), 
	_engine(engine),
	_requiredComponents(),
	_entities(),
	_updateTimepoint(SDL_GetTicks64()) {
}
		
ISystem::~ISystem() {
}

const std::string ISystem::getName() const {
	return _name;
}

// TODO improve
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
		onRegisterEntity(entity);
	}
	unlockEntities();
	return true;
}

// TODO improve
void ISystem::unregisterEntity(EntityID id) {
	lockEntities();
	auto it = _entities.find(id);
	if (it == _entities.end()) {
		unlockEntities();
		return;
	}

	onUnregisterEntity((*it).second);
	_entities.erase(id);

	unlockEntities();
}

void ISystem::update() {
	_updateTimepoint = SDL_GetTicks64();
}

bool ISystem::checkComponents(Entity* entity) const {
	if (!entity) {
		return false;
	}

	IComponent* component = nullptr;

	for (auto& componentName: _requiredComponents) {
		component = entity->getComponent(componentName);
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

void ISystem::onRegisterEntity(Entity * entity) {
}

void ISystem::onUnregisterEntity(Entity* entity) {
}

}
