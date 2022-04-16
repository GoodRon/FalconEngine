/*
 * Copyright (c) 2022, Roman Meita <theshrodingerscat@gmail.com>
 * All rights reserved
 */

#ifndef FALCON_COMPONENT_SIZE_H
#define FALCON_COMPONENT_SIZE_H

#include "IComponent.h"

namespace falcon {

class Size: public IComponent {
public:
    Size(): IComponent("Size"), width(0), heigth(0) {}

    std::shared_ptr<IComponent> clone() const override {
        return std::shared_ptr<IComponent>(new Size);
    }

	int width;
	int heigth;
};

}

#endif // FALCON_COMPONENT_SIZE_H
