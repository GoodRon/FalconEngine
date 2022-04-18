#include "PositioningSystem.h"

#include <SDL_timer.h>

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
	const uint64_t timepoint = SDL_GetTicks64();
	const uint64_t elapsedMs = timepoint - _updateTimepoint;
	_updateTimepoint = timepoint;

	Position* position = nullptr;
	Velocity* velocity = nullptr;

	for (auto& entity: _entities) {
		position = static_cast<Position*>(
			entity.second->getComponent(
				getComponentId(Position::ComponentName)));

		velocity = static_cast<Velocity*>(
			entity.second->getComponent(
				getComponentId(Velocity::ComponentName)));

		processPosition(position, velocity, elapsedMs);
	}
}

bool PositioningSystem::onEvent(
	const std::shared_ptr<firefly::IEvent>& event) {

	// TODO write me!

	return false;
}

void PositioningSystem::processPosition(
        Position* position, Velocity* velocity, uint64_t elapsedMs) const {
	if (!position || !velocity) {
		return;
	}

	position->x += velocity->speedX * elapsedMs / 1000.0;
	position->y += velocity->speedY * elapsedMs / 1000.0;
}

}
