/*
 * Copyright (c) 2022, Roman Meita <theshrodingerscat@gmail.com>
 * All rights reserved
 */

#ifndef FALCON_COMPONENT_STATE_H
#define FALCON_COMPONENT_STATE_H

#include "IComponent.h"

namespace falcon {

class State: public IComponent {
public:
    State(): IComponent("State"),
        id(0), previousId(0) {}

    std::unique_ptr<IComponent> clone() const override {
        return std::unique_ptr<IComponent>(new State);
    }

    using StateID = int;
	
    StateID id;
    StateID previousId;
};

}

#endif // FALCON_COMPONENT_STATE_H
