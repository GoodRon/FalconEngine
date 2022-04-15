/*
 * Copyright (c) 2014, Roman Meyta <theshrodingerscat@gmail.com>
 * All rights reserved
 */

#include <SDL.h>

#include "Animation.h"

namespace falcon {

Animation::Animation(const std::vector<TexturePointer>& frames,
					 const std::chrono::milliseconds& period,
					 bool isLooped) :
	IAnimation(),
	_frames(frames),
	_isLooped(isLooped),
	_speed(1.0),
	_period(period),
	_duration(0),
	_startTimepoint(std::chrono::steady_clock::now()),
	_timeOffset(0),
	_isPaused(false),
	_isEnded(true) {

	calculateDuration();
}

Animation::~Animation() {
}

void Animation::play() {
	if (_isEnded) {
		_isEnded = false;
		_startTimepoint = std::chrono::steady_clock::now();
		_timeOffset = std::chrono::milliseconds(0);
	}

	if (_isPaused) {
		_startTimepoint = std::chrono::steady_clock::now() - _timeOffset;
	}

	_isPaused = false;
}

void Animation::pause() {
	updateTimepoint();
	_isPaused = true;
}

bool Animation::isPaused() {
	updateTimepoint();
	return _isPaused;
}

void Animation::setLoop(bool isLooped) {
	_isLooped = isLooped;
}

bool Animation::isLooped() const {
	return _isLooped;
}

TexturePointer Animation::getFrame() {
	if (_frames.empty()) {
		return TexturePointer();
	}

	updateTimepoint();

	unsigned frameNumber = _timeOffset.count() * _frames.size() / _duration.count();
	if (frameNumber >= _frames.size()) {
		frameNumber = _frames.size() - 1;
	}
	return _frames[frameNumber];
}

void Animation::setPeriod(const std::chrono::milliseconds& period) {
	_period = period;
	calculateDuration();
	updateTimepoint();
}

std::chrono::milliseconds Animation::getPeriod() const {
	return _period;
}

std::chrono::milliseconds Animation::getDuration() const {
	return _duration;
}

std::chrono::milliseconds Animation::getRemainingTime() {
	updateTimepoint();
	return std::chrono::duration_cast<std::chrono::milliseconds>(
		_period * _speed) - _timeOffset;
}

void Animation::updateTimepoint() {
	if (_isPaused) {
		return;
	}

	_timeOffset = std::chrono::duration_cast<std::chrono::milliseconds>(
		std::chrono::steady_clock::now() - _startTimepoint);

	if (_isLooped) {
		_timeOffset = _timeOffset % _duration;
		_startTimepoint = std::chrono::steady_clock::now() - _timeOffset;
		return;
	}

	// Если мы не зациклены - остановимся
	if (_timeOffset > _duration) {
		_isPaused = true;
		_isEnded = true;
	}
}

void Animation::calculateDuration() {
	_duration = std::chrono::duration_cast<std::chrono::milliseconds>(_period * _speed);
}

void Animation::setSpeed(double speed) {
	if (speed <= 0.0) {
		return;
	}

	_speed = speed;
	calculateDuration();
	updateTimepoint();
}

double Animation::getSpeed() const {
	return _speed;
}

}
