/*
 * Copyright (c) 2014, Roman Meyta <theshrodingerscat@gmail.com>
 * All rights reserved
 */

#include <cmath>

#include "DirectedAnimation.h"

DirectedAnimation::DirectedAnimation() :
	IAnimation(),
	m_animations() {
}

DirectedAnimation::~DirectedAnimation() {
}

void DirectedAnimation::pushAnimation(const Animation& animation, double direction) {
	direction = fmod(direction, 360.0);
	if (direction < 0.0) {
		direction += 360.0;
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
	return getFrame(0.0);
}

TexturePointer DirectedAnimation::getFrame(double direction) {
	if (m_animations.empty()) {
		// WARNING check!
		return TexturePointer();
	}

	direction = fmod(direction, 360.0);
	if (direction < 0.0) {
		direction += 360.0;
	}

	double delta = 360.0;
	auto result = *m_animations.begin();

	for (auto &animation: m_animations) {
		double fromZero = fabs(direction - animation.first);
		double fromPi = 360.0 - fabs(direction - animation.first);
		double currentDelta = (fromZero < fromPi) ? fromZero : fromPi;

		if (currentDelta < delta) {
			delta = currentDelta;
			result = animation;
		}
	}
	return result.second.getFrame();
}
