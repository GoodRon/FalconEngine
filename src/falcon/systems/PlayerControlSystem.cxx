#include "PlayerControlSystem.h"

#include "ComponentRegistry.h"
#include "Entity.h"

namespace falcon {

PlayerControlSystem::PlayerControlSystem():
	ISystem("PlayerControl"),
	_playerComponentId(-1) {

}

PlayerControlSystem::~PlayerControlSystem() {
}

bool PlayerControlSystem::resolveComponentIDs(
    ComponentRegistry* componentRegistry) {

	if (isReady()) {
		return true;
	}

	if (!componentRegistry) {
		return false;
	}

	auto id = componentRegistry->findComponentID("Player");
	if (id < 0) {
		return false;
	}

	_playerComponentId = id;

	_isReady = true;

	return true;
}

bool PlayerControlSystem::onEvent(
    const std::shared_ptr<IEvent>& event) const {

	// TODO write me
	return true;
}

bool PlayerControlSystem::checkComponents(Entity* entity) const {
	if (!isReady()) {
		return false;
	}

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