#include "PositioningSystem.h"

#include <SDL_timer.h>

#include <firefly/Engine.h>
#include <firefly/Renderer.h>
#include <firefly/Entity.h>

#include <firefly/components/Position.h>
#include <firefly/components/Velocity.h>

namespace spacewar {

 // TODO move to helpers
constexpr double pi = 3.14159265358979323846;
const double degreesToRad = pi / 180.0;
const double radToDegrees = 180.0 / pi;

static double normalizeAngle(double angle) {
	if (fabs(angle) > 360.0) {
		angle = fmod(angle, 360.0);
	}

	if (angle < 0.0) {
		angle += 360.0;
	}
	return angle;
}

static void updateSpeed(firefly::Velocity* velocity) {
	if (!velocity) {
		return;
	}

	velocity->speedAngle = (normalizeAngle(velocity->speedAngle));

	const double speedRad = velocity->speedAngle * degreesToRad;
	velocity->speedX = velocity->speed * sin(speedRad);
	velocity->speedY = -velocity->speed * cos(speedRad);
}

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

		processPosition(position, velocity);
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
