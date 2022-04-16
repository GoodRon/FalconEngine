#include "ComponentRegistry.h"

#include "IComponent.h"

namespace falcon {

ComponentRegistry::ComponentRegistry():
	_nextId(0),
	_componentIds(),
	_prototypes() {
}

ComponentRegistry::~ComponentRegistry() {
}

/*
ComponentID ComponentRegistry::addComponent(
	const std::unique_ptr<IComponent>& prototype) {

}
*/

void ComponentRegistry::unregisterComponent(ComponentID id) {

}

ComponentID ComponentRegistry::findComponentID(
	const std::string& name) {
	if (_componentIds.find(name) == _componentIds.end()) {
		return -1;
	}
	return _componentIds[name];
}

std::shared_ptr<IComponent> ComponentRegistry::makeComponent(ComponentID id) {
	if (_prototypes.find(id) == _prototypes.end()) {
		return nullptr;
	}

	auto& prototype = _prototypes[id];
	return std::shared_ptr<IComponent>(prototype->clone());
}

void ComponentRegistry::clear() {
	_componentIds.clear();
	_prototypes.clear();
}

ComponentID ComponentRegistry::getNextId() {
	return _nextId++;
}

}
