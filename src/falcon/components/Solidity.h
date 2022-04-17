/*
 * Copyright (c) 2022, Roman Meita <theshrodingerscat@gmail.com>
 * All rights reserved
 */

#ifndef FALCON_COMPONENT_SOLIDITY_H
#define FALCON_COMPONENT_SOLIDITY_H

#include "IComponent.h"

namespace falcon {

class Solidity: public IComponent {
public:
    Solidity(): IComponent("Solidity"), isSolid(true) {}

    std::shared_ptr<IComponent> clone() const override {
        return std::shared_ptr<IComponent>(new Solidity);
    }

	bool isSolid;
};

}

#endif // FALCON_COMPONENT_SOLIDITY_H
