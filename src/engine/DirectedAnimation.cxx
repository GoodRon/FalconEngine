/*
 * Copyright (c) 2014, Roman Meyta <theshrodingerscat@gmail.com>
 * All rights reserved
 */

#include <cmath>

#include "DirectedAnimation.h"

namespace falcon {

DirectedAnimation::DirectedAnimation(const std::vector<std::pair<double, Animation>>& animations):
	IAnimation(),
	_animations(animations),
	_lastDirection(0.0) {
}

DirectedAnimation::~DirectedAnimation() {
}

void DirectedAnimation::pushAnimation(const Animation& animation, double direction) {
	direction = fmod(direction, 360.0);
	if (direction < 0.0) {
		direction += 360.0;
	}
	_animations.emplace_back(direction, animation);
}

void DirectedAnimation::play() {
	for (auto &animation: _animations) {
		animation.second.play();
	}
}

void DirectedAnimation::pause() {
	for (auto &animation: _animations) {
		animation.second.pause();
	}
}

bool DirectedAnimation::isPaused() {
	if (!_animations.empty()) {
		return _animations.begin()->second.isPaused();
	}
	return true;
}

void DirectedAnimation::setLoop(bool isLooped) {
	for (auto &animation: _animations) {
		animation.second.setLoop(isLooped);
	}
}

bool DirectedAnimation::isLooped() const {
	if (!_animations.empty()) {
		return _animations.begin()->second.isLooped();
	}
	return false;
}

TexturePointer DirectedAnimation::getFrame() {
	return getFrame(_lastDirection);
}

TexturePointer DirectedAnimation::getFrame(double direction) {
	if (_animations.empty()) {
		return TexturePointer();
	}

	direction = fmod(direction, 360.0);
	if (direction < 0.0) {
		direction += 360.0;
	}

	_lastDirection = direction;
	double delta = 360.0;
	auto result = *_animations.begin();

	for (auto &animation: _animations) {
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

}
