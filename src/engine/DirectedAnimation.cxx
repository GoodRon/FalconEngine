/*
 * Copyright (c) 2014, Roman Meyta <theshrodingerscat@gmail.com>
 * All rights reserved
 */

#include <cmath>

#include "DirectedAnimation.h"

void DirectedAnimation::pushAnimation(const Animation& animation, double direction) {
	if (direction < 0.0) {
		direction = fmod(direction, 360.0) + 360.0;
	} else {
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

bool DirectedAnimation::isPaused() {
	if (!m_animations.empty()) {
		return m_animations.begin()->second.isPaused();
	}
	return true;
}

void DirectedAnimation::setLoop(bool isLooped) {
	for (auto &animation: m_animations) {
		animation.second.setLoop(isLooped);
	}
}

bool DirectedAnimation::isLooped() const {
	if (!m_animations.empty()) {
		return m_animations.begin()->second.isLooped();
	}
	return false;
}

TexturePointer DirectedAnimation::getFrame() {
	if (m_animations.empty()) {
		// WARNING check!
		return TexturePointer();
	}

	double delta = 360.0;
	auto result = *m_animations.begin();

	for (auto &animation: m_animations) {
		double fromZero = fabs(m_direction - animation.first);
		double fromPi = 360.0 - fabs(m_direction - animation.first);
		double currentDelta = (fromZero < fromPi) ? fromZero : fromPi;
		
		if (currentDelta < delta) {
			delta = currentDelta;
			result = animation;
		}
	}
	return result.second.getFrame();
}

void DirectedAnimation::setDirection(double direction) {
	if (direction < 0.0) {
		m_direction = fmod(direction, 360.0) + 360.0;
	} else {
		m_direction = fmod(direction, 360.0);
	}
}
