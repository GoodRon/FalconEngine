#include "VelocitySystem.h"

#include <cmath>

#include <SDL_timer.h>

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
	const uint64_t timepoint = SDL_GetTicks64();
	const uint64_t elapsedMs = timepoint - _updateTimepoint;
	_updateTimepoint = timepoint;

	Velocity* velocity = nullptr;

	for (auto& entity: _entities) {
		velocity = static_cast<Velocity*>(
			entity.second->getComponent(
				getComponentId(Velocity::ComponentName)));

		processVelocity(velocity, elapsedMs);
	}
}

bool VelocitySystem::onEvent(
	const std::shared_ptr<firefly::IEvent>& event) {

	// TODO write me!

	return false;
}

double normalizeAngle(double angle) {
	if (fabs(angle) > 360.0) {
		angle = fmod(angle, 360.0);
	}

	if (angle < 0.0) {
		angle += 360.0;
	}
	return angle;
}

void VelocitySystem::processVelocity(
	Velocity* velocity, uint64_t elapsedMs) const {
	if (!velocity) {
		return;
	}

	// TODO improve

	constexpr double epsilon = 0.0001;

	velocity->accelerationAngle = (normalizeAngle(velocity->accelerationAngle));
	velocity->speedAngle = (normalizeAngle(velocity->speedAngle));

	const double accelerationRad = (velocity->accelerationAngle * M_PI) / 180.0;
	double speedRad = (velocity->speedAngle * M_PI) / 180.0;

	const double deltaSpeed = velocity->acceleration * elapsedMs / 1000.0;
	const double deltaX = deltaSpeed * cos(accelerationRad);
	const double deltaY = deltaSpeed * sin(accelerationRad);

	velocity->speedX = velocity->speed * cos(speedRad) + deltaX;
    velocity->speedY = velocity->speed * sin(speedRad) + deltaY;

    if (fabs(velocity->acceleration) < epsilon) {
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
