/*
 * Copyright (c) 2022, Roman Meita <theshrodingerscat@gmail.com>
 * All rights reserved
 */

#ifndef FIREFLY_COMPONENT_AMMUNITION_H
#define FIREFLY_COMPONENT_AMMUNITION_H

#include <unordered_map>

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

	struct Weapon {
		std::string projectile;
		int maxShots = 0;
		int currentShot = 0;
	}

	std::unordered_map<std::string, Weapon> _weapons;
};

}

#endif // FIREFLY_COMPONENT_AMMUNITION_H
