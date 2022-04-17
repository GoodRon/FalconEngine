/*
 * Copyright (c) 2022, Roman Meita <theshrodingerscat@gmail.com>
 * All rights reserved
 */

#ifndef FALCON_COMPONENT_CONTROL_H
#define FALCON_COMPONENT_CONTROL_H

#include "IComponent.h"

namespace falcon {

class Player: public IComponent {
public:
    Player(): IComponent("Player"), playerId(0) {}

    std::unique_ptr<IComponent> clone() const override {
        return std::unique_ptr<IComponent>(new Player);
    }

	int playerId;
};

}

#endif // FALCON_COMPONENT_CONTROL_H
