/*
 * Copyright (c) 2014, Roman Meyta <theshrodingerscat@gmail.com>
 * All rights reserved
 */

#ifndef ANIMATEDOBJECT_H
#define ANIMATEDOBJECT_H

#include <unordered_map>
#include <chrono>

#include "Animation.h"
#include "Directions.h"

enum AnimatedState {
	asNone,
	asStand,
	asWalk,
	asRun,
	asAttackMelee,
	asAttackRanged,
	asJump
};

class AnimatedObject {
public:
	AnimatedObject(const std::unordered_map<AnimatedState, 
				   std::unordered_map<Direction, Animation>>& animations);
	virtual ~AnimatedObject();

	void setState(AnimatedState state);
	AnimatedState getState() const;

	void setDirection(Direction direction);
	Direction getDirection() const;

	std::chrono::milliseconds getPeriod() const;
	std::chrono::milliseconds getRemainingTime() const;

private:
	AnimatedState m_state;
	Direction m_direction;
	std::unordered_map<AnimatedState, std::unordered_map<Direction, Animation>> m_animations;
};

#endif // ANIMATEDOBJECT_H
