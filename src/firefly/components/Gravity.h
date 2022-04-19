/*
 * Copyright (c) 2022, Roman Meita <theshrodingerscat@gmail.com>
 * All rights reserved
 */

#ifndef FIREFLY_COMPONENT_GRAVITY_H
#define FIREFLY_COMPONENT_GRAVITY_H

#include "IComponent.h"

namespace firefly {

class Gravity final: public IComponent {
public:
	inline static const std::string ComponentName = "Gravity";
	
	Gravity(): IComponent(ComponentName) {}
	~Gravity() override = default;

	bool hasGravity = false;
	bool emitGravity = false;
	double mass = 100000000.0;
};

}

#endif // FIREFLY_COMPONENT_GRAVITY_H
