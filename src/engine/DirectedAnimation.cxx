/*
 * Copyright (c) 2014, Roman Meyta <theshrodingerscat@gmail.com>
 * All rights reserved
 */

#include <cmath>

#include "DirectedAnimation.h"

DirectedAnimation::DirectedAnimation() :
	m_animations(),
	m_direction(0.0) {
}

void DirectedAnimation::pushAnimation(const Animation& animation, double direction) {
	// TODO сделать нормально!
	if (direction < 0.0) {
		direction = 0.0;
	} else if (direction >= 360.0) {
		direction = fmod(direction, 360.0);
	}

	m_animations.emplace_back(direction, animation);
}

void DirectedAnimation::play(bool fromStart) {
	for (auto &animation: m_animations) {
		animation.second.play(fromStart);
	}
}

void DirectedAnimation::pause() {
	for (auto &animation: m_animations) {
		animation.second.pause();
	}
}

void DirectedAnimation::setDirection(double direction) {
	m_direction = direction;
}

TexturePointer DirectedAnimation::getFrame() {
	if (m_animations.empty()) {
		// WARNING check!
		return TexturePointer();
	}

	double delta = 360.0;
	auto result = *m_animations.begin();

	for (auto &animation: m_animations) {
		if (fabs(animation.first - m_direction) < delta) {
			delta = fabs(animation.first - m_direction);
			result = animation;
		}
	}
	return result.second.getFrame();
}
