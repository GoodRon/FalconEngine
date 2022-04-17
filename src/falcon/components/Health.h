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
    Health(): IComponent("Health") {}
    ~Health() override = default;

	int max = 0;
	int current = 0;
};

}

#endif // FALCON_COMPONENT_HEALTH_H
