/*
 * Copyright (c) 2022, Roman Meita <theshrodingerscat@gmail.com>
 * All rights reserved
 */

#ifndef FALCON_COMPONENT_HEALTH_H
#define FALCON_COMPONENT_HEALTH_H

#include "IComponent.h"

namespace falcon {

class Health: public IComponent {
public:
    Health(): IComponent("Health"), max(0), current(0) {}

    IComponent* clone() const override {
        return new Health;
    }

	int max;
	int current;
};

}

#endif // FALCON_COMPONENT_HEALTH_H
