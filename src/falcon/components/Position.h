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
    Position(): IComponent("Position") {}
    ~Position() override = default;

	int x = 0;
	int y = 0;
    int width = 0;
    int heigth = 0;
    double scale = 0.0;
};

}

#endif // FALCON_COMPONENT_POSITION_H
