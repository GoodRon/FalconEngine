#include "VelocitySystem.h"

#include <firefly/Entity.h>
#include <firefly/components/Velocity.h>

#include "misc/VelocityHelpers.h"

namespace spacewar {
 
VelocitySystem::VelocitySystem(firefly::Engine* engine):
	ISystem("VelocitySystem", engine) {

	addRequiredComponent(firefly::Velocity::ComponentName);
}

VelocitySystem::~VelocitySystem() {
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
		velocity->accelerationAngle, getElapsedMs());
}

}
