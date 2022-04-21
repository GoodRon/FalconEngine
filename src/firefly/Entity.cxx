#include "Entity.h"

#include "components/IComponent.h"

namespace firefly {

static EntityID nextId() {
	static EntityID nextId = 0;
	return nextId++;
}

Entity::Entity(const std::string& name):
	_id(nextId()),
	_name(name),
	_components() {
}

// TODO check
Entity::Entity(const Entity& other) {
	operator=(other);
}

Entity& Entity::operator=(const Entity& other) {
	if (&other == this) {
		return *this;
	}

	_id = nextId();
	_name = other._name;
	_components.clear();

	std::unique_ptr<IComponent> ptr;
	for (auto& component: other._components) {
		ptr.reset(component.second->clone());
		_components[component.first] = std::move(ptr);
	}
	return *this;
}

EntityID Entity::getId() const {
	return _id;
}

const std::string Entity::getName() const {
	return _name;
}

bool Entity::addComponent(const std::string& name,
	std::unique_ptr<IComponent>&& component) {
	if (!component) {
		return false;
	}

	if (_components.find(name) != _components.end()) {
		return false;
	}

	_components[name] = std::move(component);
	return true;
}

IComponent* Entity::getComponent(const std::string& name) {
	if (_components.find(name) == _components.end()) {
		return nullptr;
	}

	return _components[name].get();
}

}
