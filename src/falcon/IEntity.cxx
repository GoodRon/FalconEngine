#include "IEntity.h"

#include "IComponent.h"

namespace falcon {

IEntity::IEntity():
	_id(-1),
	_components() {
}

IEntity::~IEntity() {
}

void IEntity::setId(EntityID id) {
	_id = id;
}

EntityID IEntity::getId() const {
	return _id;
}

bool IEntity::addComponent(const std::shared_ptr<IComponent>& component) {
	if (!component) {
		return false;
	}

	auto id = component->getId();

	if (_components.find(id) != _components.end()) {
		return false;
	}

	_components[id] = component;
	return true;
}

void IEntity::removeComponent(ComponentID id) {
	_components.erase(id);
}

std::shared_ptr<IComponent> IEntity::getComponent(ComponentID id) {
	if (_components.find(id) == _components.end()) {
		return nullptr;
	}

	return _components[id];
}

}
