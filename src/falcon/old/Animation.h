/*
 * Copyright (c) 2014, Roman Meyta <theshrodingerscat@gmail.com>
 * All rights reserved
 */

#ifndef FALCON_ANIMATION_H
#define FALCON_ANIMATION_H

#include <vector>
#include <chrono>

#include "IAnimation.h"

namespace falcon {

class Animation : public IAnimation {
public:
	Animation(const std::vector<TexturePointer>& frames,
			  const std::chrono::milliseconds& period,
			  bool isLooped = true);

	~Animation() override;

	void play() override;

	void pause() override;
	bool isPaused() override;

	void setLoop(bool isLooped) override;
	bool isLooped() const override;

	TexturePointer getFrame() override;

	void setPeriod(const std::chrono::milliseconds& period);
	std::chrono::milliseconds getPeriod() const;

	std::chrono::milliseconds getDuration() const;
	std::chrono::milliseconds getRemainingTime();

	void setSpeed(double speed);
	double getSpeed() const;

private:
	void updateTimepoint();
	void calculateDuration();

private:
	std::vector<TexturePointer> _frames;
	bool _isLooped;
	double _speed;
	std::chrono::milliseconds _period;
	std::chrono::milliseconds _duration;
	std::chrono::steady_clock::time_point _startTimepoint;
	std::chrono::milliseconds _timeOffset;
	bool _isPaused;
	bool _isEnded;
};

}

#endif // FALCON_ANIMATION_H
