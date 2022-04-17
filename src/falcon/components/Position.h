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
    Position(): IComponent("Position"), 
        x(0), y(0), width(0), heigth(0), scale(1.0) {}

    std::unique_ptr<IComponent> clone() const override {
        return std::unique_ptr<IComponent>(new Position);
    }

	int x;
	int y;
    int width;
    int heigth;
    double scale;
};

}

#endif // FALCON_COMPONENT_POSITION_H
