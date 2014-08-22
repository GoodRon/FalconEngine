/*
 * Copyright (c) 2014, Roman Meyta <theshrodingerscat@gmail.com>
 * All rights reserved
 */

#include <SDL2/SDL.h>

#include "Animation.h"

using namespace std;
using namespace chrono;

Animation::Animation(const vector<TexturePointer>& frames, 
			  		 const milliseconds& frameTime, 
			  		 bool isLooped) :
	m_frames(frames),
	m_frameTime(frameTime),
	m_isLooped(isLooped),
	m_period(m_frameTime * frames.size()),
	m_startTimepoint(steady_clock::now()),
	m_timeOffset(),
	m_isPaused(false) {
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
	m_timeOffset = duration_cast<milliseconds>(steady_clock::now() - m_startTimepoint);
	m_isPaused = true;
}

bool Animation::isPaused() const {
	return m_isPaused;
}

void Animation::setLoop(bool isLooped) {
	m_isLooped = isLooped;
}

bool Animation::isLooped() const {
	return m_isLooped;
}

TexturePointer Animation::getFrame() {
	if (!m_isPaused) {
		m_timeOffset = duration_cast<milliseconds>(steady_clock::now() - m_startTimepoint);
	}

	if (m_isLooped) {
		m_timeOffset = m_timeOffset % m_period;
	}

	// TODO сделать пересчет m_startTimepoint! чтобы не копить большие значения

	if (m_timeOffset > m_period) {
		m_timeOffset = m_period;
	}

	unsigned frameNumber = m_timeOffset / m_frameTime;
	if (frameNumber >= m_frames.size()) {
		frameNumber = m_frames.size() - 1;
	}
	return m_frames[frameNumber];
}

milliseconds Animation::getPeriod() const {
	return m_period;
}

milliseconds Animation::getRemainingTime() const {
	return m_period - m_timeOffset;
}
