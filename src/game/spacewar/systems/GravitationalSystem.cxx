#include "GravitationalSystem.h"

#include <cmath>

#include <SDL_timer.h>

#include <firefly/Engine.h>
#include <firefly/Renderer.h>
#include <firefly/Entity.h>

#include <firefly/components/Position.h>
#include <firefly/components/Velocity.h>
#include <firefly/components/Gravity.h>

namespace spacewar {

GravitationalSystem::GravitationalSystem(firefly::Engine* engine):
	firefly::ISystem("GravitationalSystem", engine) {

	_requiredComponents.push_front(firefly::Position::ComponentName);
	_requiredComponents.push_front(firefly::Velocity::ComponentName);
	_requiredComponents.push_front(firefly::Gravity::ComponentName);
}

GravitationalSystem::~GravitationalSystem() {
}

void GravitationalSystem::update() {
	const uint64_t timepoint = SDL_GetTicks64();
	const uint64_t elapsedMs = timepoint - _updateTimepoint;
	_updateTimepoint = timepoint;

	for (auto& entity: _gravityEmitters) {
		processGravity(entity.second, elapsedMs);
	}
}

bool GravitationalSystem::onEvent(
	const std::shared_ptr<firefly::IEvent>& event) {

	// TODO write me!

	return false;
}

void GravitationalSystem::onRegisterEntity(firefly::Entity* entity) {
	if (!entity) {
		return;
	}

	auto gravity = entity->getComponent<firefly::Gravity>();

	if (gravity->emitGravity) {
		_gravityEmitters[entity->getId()] = entity;
	}
}

void GravitationalSystem::onUnregisterEntity(firefly::Entity* entity) {
	if (!entity) {
		return;
	}

	_gravityEmitters.erase(entity->getId());
}

// TODO move from here
double normalizeAngle(double angle) {
	if (fabs(angle) > 360.0) {
		angle = fmod(angle, 360.0);
	}

	if (angle < 0.0) {
		angle += 360.0;
	}
	return angle;
}

// TODO check components here

void GravitationalSystem::processGravity(
        firefly::Entity* gravityEmitter,
        uint64_t elapsedMs) const {
	
	if (!gravityEmitter) {
		return;
	}

	auto emitterPosition = gravityEmitter->getComponent<firefly::Position>();
	auto emitterGravity = gravityEmitter->getComponent<firefly::Gravity>();

	// TODO improve, just testing
	constexpr double gConstant = 6.67430;
	//constexpr double gDivider = 100000000000.0;
	constexpr double gDivider = 1000.0;

	firefly::Position* position = nullptr;
	firefly::Velocity* velocity = nullptr;

	for (auto& entity: _entities) {
		if (entity.second == gravityEmitter) {
			continue;
		}

		position = entity.second->getComponent<firefly::Position>();
		velocity = entity.second->getComponent<firefly::Velocity>();
		
		// TODO use centers!
		const double distanceX = emitterPosition->x - position->x;
		const double dsistanceY = emitterPosition->y - position->y;
		const double squaredDistance = distanceX * distanceX + dsistanceY * dsistanceY;
		const double distance = sqrt(squaredDistance);

		double acceleration = 0.0;
		constexpr double epsilon = 0.0001;

		double accelerationRad = 0.0;

		if (distance > epsilon) {
			// TODO improve
			acceleration = ((gConstant * emitterGravity->mass) / gDivider) / squaredDistance;

			accelerationRad = asin(distanceX / distance);
			if (dsistanceY > 0.0) {
				accelerationRad = M_PI -accelerationRad;
			}
		}


		// TODO move to velocity

		velocity->speedAngle = (normalizeAngle(velocity->speedAngle));

		double speedRad = (velocity->speedAngle * M_PI) / 180.0;

		const double deltaSpeed = acceleration * elapsedMs / 1000.0;
		const double deltaX = deltaSpeed * sin(accelerationRad);
		const double deltaY = -deltaSpeed * cos(accelerationRad);

		velocity->speedX = velocity->speed * sin(speedRad) + deltaX;
		velocity->speedY = -velocity->speed * cos(speedRad) + deltaY;

		if (fabs(acceleration) < epsilon) {
			return;
		}

		// TODO optimize?
		velocity->speed = sqrt(velocity->speedX * velocity->speedX + 
			velocity->speedY * velocity->speedY);

		if (fabs(velocity->speed) < epsilon) {
			speedRad = 0.0;
		} else {
			speedRad = asin(velocity->speedX / velocity->speed);
			if (velocity->speedY > 0.0) {
				speedRad = M_PI -speedRad;
			}
		}

		velocity->speedAngle = speedRad * 180.0 / M_PI;
		velocity->speedAngle = (normalizeAngle(velocity->speedAngle));

		if (velocity->maxSpeed > epsilon) {
			if (velocity->speed > velocity->maxSpeed) {
				velocity->speed = velocity->maxSpeed;
				velocity->speedX = velocity->speed * sin(speedRad);
				velocity->speedY = -velocity->speed * cos(speedRad);
			}
		}
	}
}

}
