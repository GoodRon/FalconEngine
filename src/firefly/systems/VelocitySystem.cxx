#include "VelocitySystem.h"

#include <SDL_timer.h>

#include "Entity.h"

#include "components/Velocity.h"

namespace firefly {

VelocitySystem::VelocitySystem(Engine* engine):
	ISystem("VelocitySystem", engine) {

	_requiredComponents.push_front(Velocity::ComponentName);
}

VelocitySystem::~VelocitySystem() {
}

void VelocitySystem::update() {
	const uint64_t timepoint = SDL_GetTicks64();
	const uint64_t elapsedMs = timepoint - _updateTimepoint;
	_updateTimepoint = timepoint;

	Velocity* velocity = nullptr;

	for (auto& entity: _entities) {
		velocity = static_cast<Velocity*>(
			entity.second->getComponent(
				getComponentId(Velocity::ComponentName)));

		processVelocity(velocity, elapsedMs);
	}
}

bool VelocitySystem::onEvent(
	const std::shared_ptr<firefly::IEvent>& event) {

	// TODO write me!

	return false;
}

void VelocitySystem::processVelocity(
	Velocity* velocity, uint64_t elapsedMs) const {
	if (!velocity) {
		return;
	}

	const double epsilon = 0.0001;

	if (velocity->accelerationX > epsilon || velocity->accelerationX < -epsilon) {
		velocity->speedX += velocity->accelerationX * elapsedMs / 1000.0;
	}

	if (velocity->accelerationY > epsilon || velocity->accelerationY < -epsilon) {
		velocity->speedY += velocity->accelerationY * elapsedMs / 1000.0;
	}
}

}
