#include "PlayerControlSystem.h"

namespace spacewar {

PlayerControlSystem::PlayerControlSystem(
	falcon::Engine* engine):
	falcon::ISystem("PlayerControl", engine) {

}

PlayerControlSystem::~PlayerControlSystem() {

}

bool PlayerControlSystem::onEvent(
	const std::shared_ptr<falcon::IEvent>& event) const {

	// TODO write me

	return true;
}

bool PlayerControlSystem::checkComponents(
	falcon::Entity* entity) const {

	// TODO write me

	return true;
}

}
