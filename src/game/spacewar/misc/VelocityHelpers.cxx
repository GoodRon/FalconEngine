#include "VelocityHelpers.h"

#include <cmath>

#include <firefly/components/Velocity.h>
#include <firefly/components/Position.h>

namespace spacewar {

constexpr double pi = 3.14159265358979323846;
constexpr double degreesToRad = pi / 180.0;
constexpr double radToDegrees = 180.0 / pi;
constexpr double epsilon = 0.0001;

void updateSpeed(firefly::Velocity* velocity) {
	if (!velocity) {
		return;
	}

	velocity->speedDirection = (normalizeAngle(velocity->speedDirection));

	const double speedRad = velocity->speedDirection * degreesToRad;
	velocity->speedX = velocity->speed * sin(speedRad);
	velocity->speedY = -velocity->speed * cos(speedRad);
}

// TODO improve this
void addSpeed(firefly::Velocity* velocity, 
	double speed, double direction) {

	if (!velocity) {
		return;
	}

	updateSpeed(velocity);

	const double deltaSpeedRad = direction * degreesToRad;
	const double deltaSpeedX = speed * sin(deltaSpeedRad);
	const double deltaSpeedY = -speed * cos(deltaSpeedRad);

	velocity->speedX += deltaSpeedX;
	velocity->speedY += deltaSpeedY;

	velocity->speed = sqrt(velocity->speedX * velocity->speedX +
		velocity->speedY * velocity->speedY);

	double speedRad = asin(velocity->speedX / velocity->speed);
	if (velocity->speedY > 0.0) {
		speedRad = pi - speedRad;
	}

	velocity->speedDirection = speedRad * radToDegrees;
	velocity->speedDirection = (normalizeAngle(velocity->speedDirection));

	if (velocity->maxSpeed < epsilon) {
		return;
	}

	if (velocity->speed > velocity->maxSpeed) {
		velocity->speed = velocity->maxSpeed;
		updateSpeed(velocity);
	}
}

void accelerate(firefly::Velocity* velocity, double acceleration,
	double direction, uint64_t elapsedMs) {

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

	direction = (normalizeAngle(direction));

	const double accelerationRad = direction * degreesToRad;
	const double deltaSpeed = acceleration * static_cast<double>(elapsedMs) / 1000.0;
	const double deltaX = deltaSpeed * sin(accelerationRad);
	const double deltaY = -deltaSpeed * cos(accelerationRad);

	velocity->speedX += deltaX;
	velocity->speedY += deltaY;

	// TODO optimize?
	velocity->speed = sqrt(velocity->speedX * velocity->speedX + 
		velocity->speedY * velocity->speedY);

	if (fabs(velocity->speed) < epsilon) {
		velocity->speedDirection = 0.0;
		return;
	}

	double speedRad = asin(velocity->speedX / velocity->speed);
	if (velocity->speedY > 0.0) {
		speedRad = pi - speedRad;
	}

	velocity->speedDirection = speedRad * radToDegrees;
	velocity->speedDirection = (normalizeAngle(velocity->speedDirection));

	if (velocity->maxSpeed < epsilon) {
		return;
	}

	if (velocity->speed > velocity->maxSpeed) {
		velocity->speed = velocity->maxSpeed;
		updateSpeed(velocity);
	}
}


double normalizeAngle(double degrees) {
	if (fabs(degrees) > 360.0) {
		degrees = fmod(degrees, 360.0);
	}

	if (degrees < 0.0) {
		degrees += 360.0;
	}
	return degrees;
}

void movePoint(double& x, double& y, 
	double distance, double direction) {

	const double rad = direction * degreesToRad;
	const double deltaX = distance * sin(rad);
	const double deltaY = -distance * cos(rad);

	x += deltaX;
	y += deltaY;
}

void addVector(double& magnitude, double& direction,
	double& magnitudeX, double magnitudeY,
	double deltaMagnitude, double deltaDirection) {

	deltaDirection = (normalizeAngle(deltaDirection));

	const double deltaMagnitudeRad = deltaDirection * degreesToRad;
	const double deltaMagnitudeX = deltaMagnitude * sin(deltaMagnitudeRad);
	const double deltaMagnitudeY = -deltaMagnitude * cos(deltaMagnitudeRad);

	magnitudeX += deltaMagnitudeX;
	magnitudeY += deltaMagnitudeY;

	magnitude = sqrt(magnitudeX * magnitudeX + magnitudeY * magnitudeY);

	double directionRad = asin(magnitudeX / magnitude);
	if (magnitudeY > 0.0) {
		directionRad = pi - directionRad;
	}

	direction = (normalizeAngle(directionRad * radToDegrees));
}

void projectVector(double magnitude, double direction,
	double& magnitudeX, double& magnitudeY) {

	const double magnitudeRad = direction * degreesToRad;
	magnitudeX = magnitude * sin(magnitudeRad);
	magnitudeY = -magnitude * cos(magnitudeRad);
}

void limitMagnitude(double& magnitude, double& direction,
	double& magnitudeX, double& magnitudeY, double maxMagnitude) {

	constexpr double eplsilon = 0.00001;
	if (maxMagnitude < epsilon) {
		return;
	}

	if (magnitude > maxMagnitude) {
		magnitude = maxMagnitude;
		projectVector(magnitude, direction,
			magnitudeX, magnitudeY);
	}
}

}
