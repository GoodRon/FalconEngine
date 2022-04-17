#include "PlayerControlSystem.h"

#include "IComponent.h"
#include "Entity.h"

namespace falcon {

PlayerControlSystem::PlayerControlSystem():
	ISystem("PlayerControl"),
	_playerComponentId(getComponentId("Player")) {

}

PlayerControlSystem::~PlayerControlSystem() {
}

bool PlayerControlSystem::onEvent(
    const std::shared_ptr<IEvent>& event) const {

	// TODO write me
	return true;
}

bool PlayerControlSystem::checkComponents(Entity* entity) const {

	if (!entity) {
		return false;
	}

	auto component = entity->getComponent(_playerComponentId);
	if (!component) {
		return false;
	}
	return true;
}

}