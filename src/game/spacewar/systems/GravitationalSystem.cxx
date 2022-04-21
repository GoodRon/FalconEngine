#include "GravitationalSystem.h"

#include <firefly/Engine.h>
#include <firefly/Renderer.h>
#include <firefly/Entity.h>

#include <firefly/components/Position.h>
#include <firefly/components/Velocity.h>
#include <firefly/components/Gravity.h>

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

static void accelerate(firefly::Velocity* velocity, double acceleration,
	double accelerationAngle, uint64_t elapsedMs) {

	if (!velocity) {
		return;
	}

	if (!velocity->isAccelerated) {
		return;
	}

	updateSpeed(velocity);

	constexpr double epsilon = 0.0001;
	if (fabs(acceleration) < epsilon || elapsedMs == 0) {
		return;
	}

	accelerationAngle = (normalizeAngle(accelerationAngle));

	const double accelerationRad = accelerationAngle * degreesToRad;
	const double deltaSpeed = acceleration * elapsedMs / 1000.0;
	const double deltaX = deltaSpeed * sin(accelerationRad);
	const double deltaY = -deltaSpeed * cos(accelerationRad);

	velocity->speedX += deltaX;
	velocity->speedY += deltaY;

	// TODO optimize?
	velocity->speed = sqrt(velocity->speedX * velocity->speedX + 
		velocity->speedY * velocity->speedY);

	double speedRad = 0.0;
	if (fabs(velocity->speed) < epsilon) {
		speedRad = 0.0;
	} else {
		speedRad = asin(velocity->speedX / velocity->speed);
		if (velocity->speedY > 0.0) {
			speedRad = pi - speedRad;
		}
	}

	velocity->speedAngle = speedRad * radToDegrees;
	velocity->speedAngle = (normalizeAngle(velocity->speedAngle));

	if (velocity->maxSpeed < epsilon) {
		return;
	}

	if (velocity->speed > velocity->maxSpeed) {
		velocity->speed = velocity->maxSpeed;
		updateSpeed(velocity);
	}
}

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

// TODO check components here

void GravitationalSystem::processGravity(
		firefly::Entity* gravityEmitter) const {
	
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

	auto& entities = getEntities();
	for (auto& entity: entities) {
		if (entity.second == gravityEmitter) {
			continue;
		}

		position = entity.second->getComponent<firefly::Position>();
		velocity = entity.second->getComponent<firefly::Velocity>();
		
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
