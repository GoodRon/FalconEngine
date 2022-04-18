#include "PlayerControlSystem.h"

namespace spacewar {

PlayerControlSystem::PlayerControlSystem(
	firefly::Engine* engine):
	firefly::ISystem("PlayerControl", engine) {

}

PlayerControlSystem::~PlayerControlSystem() {

}

bool PlayerControlSystem::onEvent(
	const std::shared_ptr<firefly::IEvent>& event) const {

	// TODO write me

	return true;
}

bool PlayerControlSystem::checkComponents(
	firefly::Entity* entity) const {

	// TODO write me

	return true;
}

}
