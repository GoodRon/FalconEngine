/*
 * Copyright (c) 2022, Roman Meita <theshrodingerscat@gmail.com>
 * All rights reserved
 */

#ifndef FALCON_COMPONENT_POSITION_H
#define FALCON_COMPONENT_POSITION_H

#include "IComponent.h"

namespace falcon {

class Position: public IComponent {
public:
    Position(): IComponent("Position"), x(0), y(0) {}

    IComponent* clone() const override {
        return new Position;
    }

	int x;
	int y;
};

}

#endif // FALCON_COMPONENT_POSITION_H
