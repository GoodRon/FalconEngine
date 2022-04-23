/*
 * Copyright (c) 2022, Roman Meita <theshrodingerscat@gmail.com>
 * All rights reserved
 */

#ifndef SW_MISC_VELOCITY_HELPERS_H
#define SW_MISC_VELOCITY_HELPERS_H

#include <cstdint>

// TODO rename

namespace firefly {
	class Velocity;
	class Position;
}

namespace spacewar {

// TODO improve these
double normalizeAngle(double degrees);

void updateSpeed(firefly::Velocity* velocity);

void addSpeed(firefly::Velocity* velocity, 
	double speed, double direction);

void accelerate(firefly::Velocity* velocity, 
	double acceleration, double direction, 
	uint64_t elapsedMs);

void move(firefly::Position* position, 
	double distance, double angle);

}

#endif // SW_MISC_VELOCITY_HELPERS_H
