#include "VelocitySystem.h"

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
	Velocity* velocity = nullptr;

	for (auto& entity: _entities) {
		velocity = static_cast<Velocity*>(
			entity.second->getComponent(
				getComponentId(Velocity::ComponentName)));

		processVelocity(velocity);
	}
}

bool VelocitySystem::onEvent(
	const std::shared_ptr<firefly::IEvent>& event) {

	// TODO write me!

	return false;
}

void VelocitySystem::processVelocity(Velocity* velocity) const {
	if (!velocity) {
		return;
	}

	// TODO Improve

	velocity->speedX += velocity->accelerationX;
	velocity->speedY += velocity->accelerationY;
}

}
