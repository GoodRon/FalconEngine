#include "GravitationSystem.h"

#include <cmath>

#include <SDL_timer.h>

#include <firefly/Engine.h>
#include <firefly/Renderer.h>
#include <firefly/Entity.h>

#include <firefly/components/Position.h>
#include <firefly/components/Velocity.h>
#include <firefly/components/Solidity.h>

namespace spacewar {

GravitationSystem::GravitationSystem(firefly::Engine* engine):
	firefly::ISystem("GravitationSystem", engine) {

	_requiredComponents.push_front(firefly::Position::ComponentName);
	_requiredComponents.push_front(firefly::Velocity::ComponentName);
	_requiredComponents.push_front(firefly::Solidity::ComponentName);
}

GravitationSystem::~GravitationSystem() {
}

void GravitationSystem::update() {
	const uint64_t timepoint = SDL_GetTicks64();
	const uint64_t elapsedMs = timepoint - _updateTimepoint;
	_updateTimepoint = timepoint;

	firefly::Position* position = nullptr;
	firefly::Solidity* solidity = nullptr;

	for (auto& entity: _gravityEmitters) {
		processGravity(entity.second, elapsedMs);
	}
}

bool GravitationSystem::onEvent(
	const std::shared_ptr<firefly::IEvent>& event) {

	// TODO write me!

	return false;
}

void GravitationSystem::onRegisterEntity(firefly::Entity* entity) {
	if (!entity) {
		return;
	}

	auto solidity = static_cast<firefly::Solidity*>(
		entity->getComponent(
			firefly::getComponentId(firefly::Solidity::ComponentName)));

	if (solidity->hasGravity) {
		_gravityEmitters[entity->getId()] = entity;
	}
}

void GravitationSystem::onUnregisterEntity(firefly::Entity* entity) {
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

void GravitationSystem::processGravity(
        firefly::Entity* gravityEmitter,
        uint64_t elapsedMs) const {
	
	if (!gravityEmitter) {
		return;
	}

	auto gravityPosition = static_cast<firefly::Position*>(
		gravityEmitter->getComponent(
			firefly::getComponentId(firefly::Position::ComponentName)));


	// TODO improve, just testing
	const double gravityAcceleration = 3000000.0;

	firefly::Position* position = nullptr;
	firefly::Velocity* velocity = nullptr;

	for (auto& entity: _entities) {
		if (entity.second == gravityEmitter) {
			continue;
		}

		position = static_cast<firefly::Position*>(
			entity.second->getComponent(
				firefly::getComponentId(firefly::Position::ComponentName)));

		velocity = static_cast<firefly::Velocity*>(
			entity.second->getComponent(
				firefly::getComponentId(firefly::Velocity::ComponentName)));

		// TODO use centers!
		const double distanceX = gravityPosition->x - position->x;
		const double dsistanceY = gravityPosition->y - position->y;
		const double squaredDistance = distanceX * distanceX + dsistanceY * dsistanceY;
		const double distance = sqrt(squaredDistance);

		double acceleration = 0.0;
		const double epsilon = 0.0001;

		double accelerationRad = 0.0;

		if (distance > epsilon) {
			acceleration = gravityAcceleration / squaredDistance;

			accelerationRad = acos(distanceX / distance);
			if (dsistanceY < 0.0) {
				accelerationRad = -accelerationRad;
			}
		}



		// TODO move to velocity

		velocity->speedAngle = (normalizeAngle(velocity->speedAngle));

		double speedRad = (velocity->speedAngle * M_PI) / 180.0;

		const double deltaSpeed = acceleration * elapsedMs / 1000.0;
		const double deltaX = deltaSpeed * cos(accelerationRad);
		const double deltaY = deltaSpeed * sin(accelerationRad);

		velocity->speedX = velocity->speed * cos(speedRad) + deltaX;
		velocity->speedY = velocity->speed * sin(speedRad) + deltaY;

		if (fabs(acceleration) < epsilon) {
			return;
		}

		// TODO optimize?
		velocity->speed = sqrt(velocity->speedX * velocity->speedX + 
			velocity->speedY * velocity->speedY);

		if (fabs(velocity->speed) < epsilon) {
			speedRad = 0.0;
		} else {
			speedRad = acos(velocity->speedX / velocity->speed);
			if (velocity->speedY < 0.0) {
				speedRad = -speedRad;
			}
		}

		velocity->speedAngle = speedRad * 180.0 / M_PI;
		velocity->speedAngle = (normalizeAngle(velocity->speedAngle));

		if (velocity->maxSpeed > epsilon) {
			if (velocity->speed > velocity->maxSpeed) {
				velocity->speed = velocity->maxSpeed;
				velocity->speedX = velocity->speed * cos(speedRad);
				velocity->speedY = velocity->speed * sin(speedRad);
			}
		}
	}
}

}
