/*
 * Copyright (c) 2022, Roman Meita <theshrodingerscat@gmail.com>
 * All rights reserved
 */

#ifndef FIREFLY_COMPONENT_HEALTH_H
#define FIREFLY_COMPONENT_HEALTH_H

#include "IComponent.h"

namespace firefly {

class Health: public IComponent {
public:
    Health(): IComponent("Health") {}
    ~Health() override = default;

	int max = 0;
	int current = 0;
};

}

#endif // FIREFLY_COMPONENT_HEALTH_H
