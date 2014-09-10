/*
 * Copyright (c) 2014, Roman Meyta <theshrodingerscat@gmail.com>
 * All rights reserved
 */

#ifndef DIRECTEDANIMATION_H
#define DIRECTEDANIMATION_H

#include <vector>

#include "Animation.h"

class DirectedAnimation {
public:
	DirectedAnimation();

	/**
	 * @brief Добавить анимацию 
	 *
	 * @param animation
	 * @param direction направление от 0 до 360 градусов
	 * @return void
	 */
	void pushAnimation(const Animation& animation, double direction);
	
	void play(bool fromStart = false);

	void pause();

	void setDirection(double direction);

	TexturePointer getFrame();
	
private:
	std::vector<std::pair<double, Animation>> m_animations;
	double m_direction;
};

#endif // DIRECTEDANIMATION_H
