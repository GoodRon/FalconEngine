#include "PositioningSystem.h"

#include <SDL_timer.h>

#include <firefly/Engine.h>
#include <firefly/Renderer.h>
#include <firefly/Entity.h>

#include <firefly/components/Position.h>
#include <firefly/components/Velocity.h>

#include "misc/VelocityHelpers.h"

namespace spacewar {

PositioningSystem::PositioningSystem(firefly::Engine* engine):
	firefly::ISystem("PositioningSystem", engine) {

	addRequiredComponent(firefly::Position::ComponentName);
	addRequiredComponent(firefly::Velocity::ComponentName);
}

PositioningSystem::~PositioningSystem() {
}

void PositioningSystem::onUpdate() {
	firefly::Position* position = nullptr;
	firefly::Velocity* velocity = nullptr;

	auto& entities = getEntities();
	for (auto& entity: entities) {
		position = entity.second->getComponent<firefly::Position>();
		velocity = entity.second->getComponent<firefly::Velocity>();

		if (velocity->isActive) {
			processPosition(position, velocity);
		}
	}
}

void PositioningSystem::processPosition(
		firefly::Position* position, firefly::Velocity* velocity) const {
	
	if (!position || !velocity) {
		return;
	}

	updateSpeed(velocity);

	const auto elapsedMs = getElapsedMs();

	position->x += velocity->speedX * elapsedMs / 1000.0;
	position->y += velocity->speedY * elapsedMs / 1000.0;

	auto renderer = getEngine()->getRenderer();
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
