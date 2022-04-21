#include "VelocityHelpers.h"

#include <cmath>

#include <firefly/components/Velocity.h>

namespace spacewar {

constexpr double pi = 3.14159265358979323846;
constexpr double degreesToRad = pi / 180.0;
constexpr double radToDegrees = 180.0 / pi;
constexpr double epsilon = 0.0001;

double normalizeAngle(double degrees) {
	if (fabs(degrees) > 360.0) {
		degrees = fmod(degrees, 360.0);
	}

	if (degrees < 0.0) {
		degrees += 360.0;
	}
	return degrees;
}

void updateSpeed(firefly::Velocity* velocity) {
	if (!velocity) {
		return;
	}

	velocity->speedAngle = (normalizeAngle(velocity->speedAngle));

	const double speedRad = velocity->speedAngle * degreesToRad;
	velocity->speedX = velocity->speed * sin(speedRad);
	velocity->speedY = -velocity->speed * cos(speedRad);
}

void accelerate(firefly::Velocity* velocity, double acceleration,
	double accelerationAngle, uint64_t elapsedMs) {

	if (!velocity) {
		return;
	}

	if (!velocity->isAccelerated) {
		return;
	}

	updateSpeed(velocity);

	if (fabs(acceleration) < epsilon || elapsedMs == 0) {
		return;
	}

	accelerationAngle = (normalizeAngle(accelerationAngle));

	const double accelerationRad = accelerationAngle * degreesToRad;
	const double deltaSpeed = acceleration * static_cast<double>(elapsedMs) / 1000.0;
	const double deltaX = deltaSpeed * sin(accelerationRad);
	const double deltaY = -deltaSpeed * cos(accelerationRad);

	velocity->speedX += deltaX;
	velocity->speedY += deltaY;

	// TODO optimize?
	velocity->speed = sqrt(velocity->speedX * velocity->speedX + 
		velocity->speedY * velocity->speedY);

	if (fabs(velocity->speed) < epsilon) {
		velocity->speedAngle = 0.0;
		return;
	}

	double speedRad = asin(velocity->speedX / velocity->speed);
	if (velocity->speedY > 0.0) {
		speedRad = pi - speedRad;
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

}
