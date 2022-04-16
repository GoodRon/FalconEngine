#include "ComponentRegister.h"

#include "IComponent.h"

namespace falcon {

ComponentRegister::ComponentRegister():
	_nextId(0),
	_componentIds(),
	_prototypes() {
}

ComponentRegister::~ComponentRegister() {
}

/*
ComponentID ComponentRegister::addComponent(
	const std::unique_ptr<IComponent>& prototype) {

}
*/

void ComponentRegister::unregisterComponent(ComponentID id) {

}

ComponentID ComponentRegister::findComponentID(
	const std::string& name) {
	if (_componentIds.find(name) == _componentIds.end()) {
		return -1;
	}
	return _componentIds[name];
}

std::shared_ptr<IComponent> ComponentRegister::makeComponent(ComponentID id) {
	if (_prototypes.find(id) == _prototypes.end()) {
		return nullptr;
	}

	auto& prototype = _prototypes[id];
	return std::shared_ptr<IComponent>(prototype->clone());
}

void ComponentRegister::clear() {
	_componentIds.clear();
	_prototypes.clear();
}

ComponentID ComponentRegister::getNextId() {
	return _nextId++;
}

}
