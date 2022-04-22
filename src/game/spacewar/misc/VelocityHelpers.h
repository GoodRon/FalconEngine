/*
 * Copyright (c) 2022, Roman Meita <theshrodingerscat@gmail.com>
 * All rights reserved
 */

#ifndef SW_MISC_VELOCITY_HELPERS_H
#define SW_MISC_VELOCITY_HELPERS_H

#include <cstdint>

namespace firefly {
	class Velocity;
	class Position;
}

namespace spacewar {

double normalizeAngle(double degrees);

void updateSpeed(firefly::Velocity* velocity);

void accelerate(firefly::Velocity* velocity, 
	double acceleration, double accelerationAngle, 
	uint64_t elapsedMs);

void move(firefly::Position* position, 
	double distance, double angle);

}

#endif // SW_MISC_VELOCITY_HELPERS_H
