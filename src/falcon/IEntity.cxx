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

bool IEntity::addComponent(std::unique_ptr<IComponent>& component) {
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

IComponent* IEntity::getComponent(ComponentID id) {
	if (_components.find(id) == _components.end()) {
		return nullptr;
	}

	return _components[id].get();
}

}
