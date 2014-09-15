/*
 * Copyright (c) 2014, Roman Meyta <theshrodingerscat@gmail.com>
 * All rights reserved
 */

#include <SDL2/SDL.h>

#include "Animation.h"

using namespace std;
using namespace chrono;

Animation::Animation(const vector<TexturePointer>& frames, 
			  		 const milliseconds& period, 
			  		 bool isLooped) :
	m_frames(frames),
	m_isLooped(isLooped),
	m_period(period),
	m_startTimepoint(steady_clock::now()),
	m_timeOffset(0),
	m_isPaused(true) {
}

void Animation::recalculateTimes() {
	if (m_isPaused) {
		return;
	}

	m_timeOffset = duration_cast<milliseconds>(steady_clock::now() - m_startTimepoint);

	if (m_isLooped) {
		m_timeOffset = m_timeOffset % m_period;
		m_startTimepoint = steady_clock::now() - m_timeOffset;
	}

	// Если мы не зациклены - остановимся
	if (m_timeOffset > m_period) {
		m_timeOffset = m_period;
		m_isPaused = true;
	}
}

void Animation::play(bool fromStart) {
	if (fromStart) {
		m_timeOffset = milliseconds(0);
		m_startTimepoint = steady_clock::now();
	}

	if (m_isPaused) {
		m_isPaused = false;
		m_startTimepoint = steady_clock::now() - m_timeOffset;
	}
}

void Animation::pause() {
	recalculateTimes();
	m_isPaused = true;
}

bool Animation::isPaused() {
	recalculateTimes();
	return m_isPaused;
}

void Animation::setLoop(bool isLooped) {
	m_isLooped = isLooped;
}

bool Animation::isLooped() const {
	return m_isLooped;
}

TexturePointer Animation::getFrame() {
	if (m_frames.empty()) {
		// WARNING check!
		return TexturePointer();
	}

	recalculateTimes();

	unsigned frameNumber = m_timeOffset * m_frames.size() / m_period;
	if (frameNumber >= m_frames.size()) {
		frameNumber = m_frames.size() - 1;
	}
	return m_frames[frameNumber];
}

void Animation::setPeriod(const milliseconds& period) {
	m_period = period;
	recalculateTimes();
}

milliseconds Animation::getPeriod() const {
	return m_period;
}

milliseconds Animation::getRemainingTime() {
	recalculateTimes();
	return m_period - m_timeOffset;
}
