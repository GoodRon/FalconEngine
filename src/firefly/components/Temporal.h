/*
 * Copyright (c) 2022, Roman Meita <theshrodingerscat@gmail.com>
 * All rights reserved
 */

#ifndef FIREFLY_COMPONENT_TEMPORAL_H
#define FIREFLY_COMPONENT_TEMPORAL_H

#include "IComponent.h"

namespace firefly {

class Temporal final: public IComponent {
public:
	inline static const std::string ComponentName = "Temporal";
	
	Temporal(): IComponent(ComponentName) {}
	~Temporal() override = default;

	Temporal(const Temporal&) = default;
	Temporal& operator=(const Temporal&) = default;

	IComponent* clone() const override {
		return new Temporal(*this);
	}

	uint64_t timeToLiveMs = 0;
	uint64_t timepoint = 0;
};

}

#endif // FIREFLY_COMPONENT_TEMPORAL_H
