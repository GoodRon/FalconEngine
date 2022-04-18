#include "PlayerControlSystem.h"

#include "Entity.h"

#include "components/IComponent.h"

namespace firefly {

PlayerControlSystem::PlayerControlSystem(Engine* engine):
	ISystem("PlayerControl", engine) {

}

PlayerControlSystem::~PlayerControlSystem() {
}

bool PlayerControlSystem::onEvent(
    const std::shared_ptr<IEvent>& event) const {

	// TODO write me
	return true;
}

}