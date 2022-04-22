#include "VelocitySystem.h"

#include <firefly/Entity.h>
#include <firefly/components/Velocity.h>

#include <firefly/events/SpeedEvent.h>

#include "misc/VelocityHelpers.h"

namespace spacewar {
 
VelocitySystem::VelocitySystem(firefly::Engine* engine):
	ISystem("VelocitySystem", engine) {

	addRequiredComponent(firefly::Velocity::ComponentName);
}

VelocitySystem::~VelocitySystem() {
}

bool VelocitySystem::onEvent(
	const std::shared_ptr<firefly::IEvent>& event) {

	switch (event->getType()) {
	case firefly::EventType::Speed: {
		const auto speedEvent = 
			static_cast<firefly::SpeedEvent*>(event.get());
		if (!speedEvent) {
			return false;
		}

		updateSpeed(speedEvent->getId(),
			speedEvent->getSpeed(),
			speedEvent->getDirection());
		return true;
	} break;

	default:
		break;
	}

	return false;
}

void VelocitySystem::onUpdate() {
	firefly::Velocity* velocity = nullptr;

	auto& entities = getEntities();
	for (auto& entity: entities) {
		velocity = entity.second->getComponent<firefly::Velocity>();

		if (velocity->isActive) {
			processVelocity(velocity);
		}
	}
}

void VelocitySystem::processVelocity(
	firefly::Velocity* velocity) const {
	if (!velocity) {
		return;
	}

	accelerate(velocity, velocity->acceleration,
		velocity->accelerationDirection, getElapsedMs());
}


void VelocitySystem::updateSpeed(firefly::EntityID id, 
	double speed, double direction) const {

	const auto entity = getEntity(id);
	if (!entity) {
		return;
	}

	const auto velocity = entity->getComponent<firefly::Velocity>();
	if (!velocity) {
		return;
	}

	velocity->speed = speed;
	velocity->speedDirection = direction;
}

}
