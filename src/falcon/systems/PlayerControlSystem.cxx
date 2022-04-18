#include "PlayerControlSystem.h"

#include "Entity.h"

#include "components/IComponent.h"

namespace falcon {

PlayerControlSystem::PlayerControlSystem(Engine* engine):
	ISystem("PlayerControl", engine),
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