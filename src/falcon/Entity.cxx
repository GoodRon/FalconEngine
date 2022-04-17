#include "Entity.h"

#include "IComponent.h"

namespace falcon {

static EntityID nextId() {
	static EntityID nextId = 0;
	return nextId++;
}

Entity::Entity():
	_id(nextId()),
	_components() {
}

Entity::~Entity() {
}

EntityID Entity::getId() const {
	return _id;
}

bool Entity::addComponent(std::unique_ptr<IComponent>& component) {
	if (!component) {
		return false;
	}

	auto id = component->getId();

	if (_components.find(id) != _components.end()) {
		return false;
	}

	_components[id].swap(component);
	return true;
}

IComponent* Entity::getComponent(ComponentID id) {
	if (_components.find(id) == _components.end()) {
		return nullptr;
	}

	return _components[id].get();
}

}
