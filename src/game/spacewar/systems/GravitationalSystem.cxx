#include "GravitationalSystem.h"

#include <firefly/Engine.h>
#include <firefly/Renderer.h>
#include <firefly/Entity.h>

#include <firefly/components/Position.h>
#include <firefly/components/Velocity.h>
#include <firefly/components/Gravity.h>

#include "misc/VelocityHelpers.h"

namespace spacewar {

constexpr double pi = 3.14159265358979323846;
constexpr double radToDegrees = 180.0 / pi;

GravitationalSystem::GravitationalSystem(firefly::Engine* engine):
	firefly::ISystem("GravitationalSystem", engine) {

	addRequiredComponent(firefly::Position::ComponentName);
	addRequiredComponent(firefly::Velocity::ComponentName);
	addRequiredComponent(firefly::Gravity::ComponentName);
}

GravitationalSystem::~GravitationalSystem() {
}

void GravitationalSystem::onUpdate() {
	for (auto& entity: _gravityEmitters) {
		processGravity(entity.second);
	}
}

bool GravitationalSystem::onRegisterEntity(firefly::Entity* entity) {
	if (!entity) {
		return false;
	}

	auto gravity = entity->getComponent<firefly::Gravity>();

	if (gravity->emitGravity) {
		_gravityEmitters[entity->getId()] = entity;
	}
	return true;
}

void GravitationalSystem::onUnregisterEntity(firefly::Entity* entity) {
	if (!entity) {
		return;
	}

	_gravityEmitters.erase(entity->getId());
}

void GravitationalSystem::processGravity(
		firefly::Entity* gravityEmitter) const {
	
	if (!gravityEmitter) {
		return;
	}

	auto emitterPosition = gravityEmitter->getComponent<firefly::Position>();
	auto emitterGravity = gravityEmitter->getComponent<firefly::Gravity>();

	if (!emitterGravity->isActive) {
		return;
	}

	// TODO improve, just testing
	constexpr double gConstant = 6.67430;
	//constexpr double gDivider = 100000000000.0;
	constexpr double gDivider = 1000.0;

	firefly::Position* position = nullptr;
	firefly::Velocity* velocity = nullptr;
	firefly::Gravity* gravity = nullptr;

	auto& entities = getEntities();
	for (auto& entity: entities) {
		if (entity.second == gravityEmitter) {
			continue;
		}

		position = entity.second->getComponent<firefly::Position>();
		velocity = entity.second->getComponent<firefly::Velocity>();
		gravity = entity.second->getComponent<firefly::Gravity>();

		if (!velocity->isActive || !gravity->isActive) {
			continue;
		}
		
		// TODO use centers!
		const double distanceX = emitterPosition->x - position->x;
		const double dsistanceY = emitterPosition->y - position->y;
		const double squaredDistance = distanceX * distanceX + dsistanceY * dsistanceY;
		
		constexpr double epsilon = 0.0001;
		if (squaredDistance < epsilon) {
			continue;
		}

		const double distance = sqrt(squaredDistance);

		// TODO improve
		const double acceleration = ((gConstant * emitterGravity->mass) / gDivider) / squaredDistance;

		double accelerationRad = asin(distanceX / distance);
		if (dsistanceY > 0.0) {
			accelerationRad = M_PI -accelerationRad;
		}

		accelerate(velocity, acceleration, 
			accelerationRad * radToDegrees, getElapsedMs());
	}
}

}
