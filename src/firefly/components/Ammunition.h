/*
 * Copyright (c) 2022, Roman Meita <theshrodingerscat@gmail.com>
 * All rights reserved
 */

#ifndef FIREFLY_COMPONENT_AMMUNITION_H
#define FIREFLY_COMPONENT_AMMUNITION_H

#include "IComponent.h"

namespace firefly {

class Ammunition final: public IComponent {
public:
	inline static const std::string ComponentName = "Ammunition";
	
	Ammunition(): IComponent(ComponentName) {}
	~Ammunition() override = default;

	Ammunition(const Ammunition&) = default;
	Ammunition& operator=(const Ammunition&) = default;

	IComponent* clone() const override {
		return new Ammunition(*this);
	}

	int max = 0;
	int current = 0;
};

}

#endif // FIREFLY_COMPONENT_AMMUNITION_H
