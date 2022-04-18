#include "PositioningSystem.h"

#include "Entity.h"

#include "components/Position.h"
#include "components/Velocity.h"

namespace firefly {

PositioningSystem::PositioningSystem(Engine* engine):
	ISystem("PositioningSystem", engine) {

	_requiredComponents.push_front(Position::ComponentName);
	_requiredComponents.push_front(Velocity::ComponentName);
}

PositioningSystem::~PositioningSystem() {
}

void PositioningSystem::update() {
	Position* position = nullptr;
	Velocity* velocity = nullptr;

	for (auto& entity: _entities) {
		position = static_cast<Position*>(
			entity.second->getComponent(
				getComponentId(Position::ComponentName)));

		velocity = static_cast<Velocity*>(
			entity.second->getComponent(
				getComponentId(Velocity::ComponentName)));

		processPosition(position, velocity);
	}
}

bool PositioningSystem::onEvent(
	const std::shared_ptr<firefly::IEvent>& event) const {

	// TODO write me!

	return false;
}

void PositioningSystem::processPosition(
        Position* position, Velocity* velocity) const {
	if (!position || !velocity) {
		return;
	}

	position->x += velocity->speedX;
	position->y += velocity->speedY;
}

}
