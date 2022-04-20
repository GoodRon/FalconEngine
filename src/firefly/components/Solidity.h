/*
 * Copyright (c) 2022, Roman Meita <theshrodingerscat@gmail.com>
 * All rights reserved
 */

#ifndef FIREFLY_COMPONENT_SOLIDITY_H
#define FIREFLY_COMPONENT_SOLIDITY_H

#include "IComponent.h"

namespace firefly {

class Solidity final: public IComponent {
public:
	inline static const std::string ComponentName = "Solidity";
	
	Solidity(): IComponent(ComponentName) {}
	~Solidity() override = default;

	Solidity(const Solidity&) = default;
	Solidity& operator=(const Solidity&) = default;

	IComponent* clone() const override {
		return new Solidity(*this);
	}

	bool isSolid = false;
	bool isDestructable = false;
	// collision box
};

}

#endif // FIREFLY_COMPONENT_SOLIDITY_H
