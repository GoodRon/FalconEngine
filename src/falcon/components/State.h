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
    State(): IComponent("State") {}
    ~State() override = default;

    using StateID = int;
	
    StateID id = 0;
    StateID previousId = 0;
};

}

#endif // FALCON_COMPONENT_STATE_H
