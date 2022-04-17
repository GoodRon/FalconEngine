#include "GameObject.h"

#include "Entity.h"

namespace falcon {

GameObject::GameObject(
	const std::shared_ptr<Entity>& entity):
	_entity(entity) {
}

GameObject::~GameObject() {
}

EntityID GameObject::getId() const {
	return _entity->getId();
}

std::shared_ptr<Entity> GameObject::getEntity() const {
	return _entity;
}

bool GameObject::onEvent(const std::shared_ptr<IEvent>& event) {
	// TODO write me

	return processEvent(event);
}

bool GameObject::processEvent(const std::shared_ptr<IEvent>& event) {
	// TODO write me
	return false;
}

}
