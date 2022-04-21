#include "VelocitySystem.h"

#include "Entity.h"

#include "components/Velocity.h"

namespace firefly {
 
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

static void updateSpeed(Velocity* velocity) {
	if (!velocity) {
		return;
	}

	velocity->speedAngle = (normalizeAngle(velocity->speedAngle));

	const double speedRad = velocity->speedAngle * degreesToRad;
	velocity->speedX = velocity->speed * sin(speedRad);
	velocity->speedY = -velocity->speed * cos(speedRad);
}

static void accelerate(Velocity* velocity, double acceleration,
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

VelocitySystem::VelocitySystem(Engine* engine):
	ISystem("VelocitySystem", engine) {

	addRequiredComponent(Velocity::ComponentName);
}

VelocitySystem::~VelocitySystem() {
}

void VelocitySystem::onUpdate() {
	Velocity* velocity = nullptr;

	auto& entities = getEntities();
	for (auto& entity: entities) {
		velocity = entity.second->getComponent<Velocity>();
		processVelocity(velocity);
	}
}

void VelocitySystem::processVelocity(
	Velocity* velocity) const {
	if (!velocity) {
		return;
	}

	accelerate(velocity, velocity->acceleration,
		velocity->accelerationAngle, getElapsedMs());
}

}
