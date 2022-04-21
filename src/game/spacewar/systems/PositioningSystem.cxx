#include "PositioningSystem.h"

#include <SDL_timer.h>

#include <firefly/Engine.h>
#include <firefly/Renderer.h>
#include <firefly/Entity.h>

#include <firefly/components/Position.h>
#include <firefly/components/Velocity.h>

namespace spacewar {

PositioningSystem::PositioningSystem(firefly::Engine* engine):
	firefly::ISystem("PositioningSystem", engine) {

	_requiredComponents.push_front(firefly::Position::ComponentName);
	_requiredComponents.push_front(firefly::Velocity::ComponentName);
}

PositioningSystem::~PositioningSystem() {
}

void PositioningSystem::update() {
	const uint64_t timepoint = SDL_GetTicks64();
	const uint64_t elapsedMs = timepoint - _updateTimepoint;
	_updateTimepoint = timepoint;

	firefly::Position* position = nullptr;
	firefly::Velocity* velocity = nullptr;

	for (auto& entity: _entities) {
		position = entity.second->getComponent<firefly::Position>();
		velocity = entity.second->getComponent<firefly::Velocity>();

		processPosition(position, velocity, elapsedMs);
	}
}

bool PositioningSystem::onEvent(
	const std::shared_ptr<firefly::IEvent>& event) {

	// TODO write me!

	return false;
}

void PositioningSystem::processPosition(
        firefly::Position* position, firefly::Velocity* velocity, 
        uint64_t elapsedMs) const {
	
	if (!position || !velocity) {
		return;
	}

	position->x += velocity->speedX * elapsedMs / 1000.0;
	position->y += velocity->speedY * elapsedMs / 1000.0;

	auto renderer = _engine->getRenderer();
	SDL_Rect windowRect = renderer->getViewport();

	if ((position->x + position->centerX) > (windowRect.w + position->width)) {
		position->x = -position->width;
	}

	if ((position->x + position->centerX) < (-position->width)) {
		position->x = windowRect.w;
	}

	if ((position->y + position->centerY) > (windowRect.h + position->height)) {
		position->y = -position->height;
	}

	if ((position->y + position->centerY) < (-position->height)) {
		position->y = windowRect.h;
	}
}

}
