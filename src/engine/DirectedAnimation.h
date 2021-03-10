/*
 * Copyright (c) 2014, Roman Meyta <theshrodingerscat@gmail.com>
 * All rights reserved
 */

#ifndef FALCON_DIRECTED_ANIMATION_H
#define FALCON_DIRECTED_ANIMATION_H

#include "Animation.h"

namespace falcon {

class DirectedAnimation : public IAnimation {
public:
	DirectedAnimation(const std::vector<std::pair<double, Animation>>& animations);

	~DirectedAnimation() override;

	// TODO remove
	void pushAnimation(const Animation& animation, double direction);

	void play() override;

	void pause() override;

	bool isPaused() override;

	void setLoop(bool isLooped) override;

	bool isLooped() const override;

	TexturePointer getFrame() override;

	TexturePointer getFrame(double direction) override;

private:
	std::vector<std::pair<double, Animation>> _animations;
	double _lastDirection;
};

}

#endif // FALCON_DIRECTED_ANIMATION_H
