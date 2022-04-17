#include "Entity.h"

#include "IComponent.h"

namespace falcon {

static EntityID nextId() {
	static EntityID nextId = 0;
	return nextId++;
}

Entity::Entity(const std::string& name):
	_id(nextId()),
	_name(name),
	_components() {
}

Entity::~Entity() {
}

EntityID Entity::getId() const {
	return _id;
}

const std::string Entity::getName() const {
	return _name;
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
