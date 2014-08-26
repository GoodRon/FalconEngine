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
	DirectedAnimation(const std::vector<Animation>& animations);
	

	
private:
	std::vector<Animation> m_animations;
	
};

#endif // DIRECTEDANIMATION_H
