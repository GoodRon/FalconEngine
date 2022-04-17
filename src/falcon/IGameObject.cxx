#include "IGameObject.h"

#include "Entity.h"

namespace falcon {

IGameObject::IGameObject(
	const std::shared_ptr<Entity>& entity):
	_entity(entity) {
}

IGameObject::~IGameObject() {
}

EntityID IGameObject::getId() const {
	return _entity->getId();
}

/*
std::shared_ptr<Entity> IGameObject::getEntity() const {
	return _entity;
}
*/

bool IGameObject::onEvent(const std::shared_ptr<IEvent>& event) {
	// TODO write me

	return processEvent(event);
}

bool IGameObject::processEvent(const std::shared_ptr<IEvent>& event) {
	// TODO write me
	return false;
}

}
