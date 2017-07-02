/*
 * Copyright (c) 2014, Roman Meyta <theshrodingerscat@gmail.com>
 * All rights reserved
 */

#include <SDL2/SDL.h>

#include "Animation.h"

using namespace std;
using namespace chrono;

Animation::Animation(const map<Direction, Frames>& frames,
					 const milliseconds& period,
					 bool isLooped) :
	_frames(frames),
	_isLooped(isLooped),
	_period(period),
	_startTimepoint(steady_clock::now()),
	_timeOffset(milliseconds(0)),
	_isPaused(true),
	_speedModificator(1.0) {
}

Animation::~Animation() {
}

void Animation::play(bool fromStart) {
	if (fromStart) {
		_timeOffset = milliseconds(0);
		_startTimepoint = steady_clock::now();
	}

	if (_isPaused) {
		_isPaused = false;
		_startTimepoint = steady_clock::now() - _timeOffset;
	}
}

void Animation::pause() {
	recalculateTimes();
	_isPaused = true;
}

bool Animation::isPaused() const {
	return _isPaused;
}

void Animation::setLoop(bool isLooped) {
	_isLooped = isLooped;
}

bool Animation::isLooped() const {
	return _isLooped;
}

Texture Animation::getFrame(Direction direction) {
	if (_frames.find(direction) == _frames.end()) {
		// WARNING check!
		return Texture();
	}

	recalculateTimes();

	auto frames = _frames[direction];

	unsigned frameNumber = _timeOffset * frames.size() / (_period * _speed);
	if (frameNumber >= frames.size()) {
		frameNumber = frames.size() - 1;
	}
	return frames[frameNumber];
}

void Animation::setPeriod(const milliseconds& period) {
	_period = period;
	recalculateTimes();
}

milliseconds Animation::getPeriod() const {
	return _period;
}

milliseconds Animation::getRemainingTime() {
	recalculateTimes();
	return duration_cast<milliseconds>(_period * _speed) - _timeOffset;
}

void Animation::recalculateTimes() {
	if (_isPaused) {
		return;
	}

	_timeOffset = duration_cast<milliseconds>(steady_clock::now() - _startTimepoint);

	if (_isLooped) {
		_timeOffset = _timeOffset % duration_cast<milliseconds>(_period * _speed);
		_startTimepoint = steady_clock::now() - _timeOffset;
		return;
	}

	// Если мы не зациклены - остановимся
	if (_timeOffset > duration_cast<milliseconds>(_period * _speed)) {
		_timeOffset = duration_cast<milliseconds>(_period * _speed);
		_isPaused = true;
	}
}
