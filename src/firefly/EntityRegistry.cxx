#include "EntityRegistry.h"

#include "Entity.h"

#include "components/IComponent.h"

namespace firefly {

EntityRegistry::EntityRegistry():
	_prototypes() {
}

bool EntityRegistry::registerEntity(
	const std::string& name,
	std::unique_ptr<Entity>& prototype) {

	if (!prototype) {
		return false;
	}

	if (hasEntity(name)) {
		return false;
	}

	_prototypes[name] = std::move(prototype);
	return true;
}

std::shared_ptr<Entity> EntityRegistry::makeEntity(const std::string& name) {
	if (!hasEntity(name)) {
		return nullptr;
	}

	std::shared_ptr<Entity> entity(new Entity);
	(*entity.get()) = (*_prototypes[name].get());

	return entity;
}

bool EntityRegistry::hasEntity(const std::string& name) const {
	if (_prototypes.find(name) == _prototypes.end()) {
		return false;
	}
	return true;
}

void EntityRegistry::clear() {
	_prototypes.clear();
}

}
