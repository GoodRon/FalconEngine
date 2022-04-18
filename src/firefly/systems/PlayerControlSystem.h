/*
 * Copyright (c) 2022, Roman Meita <theshrodingerscat@gmail.com>
 * All rights reserved
 */

#ifndef FIREFLY_SYSTEMS_PLAYER_CONTROL_H
#define FIREFLY_SYSTEMS_PLAYER_CONTROL_H

#include "ISystem.h"

namespace firefly {

using ComponentID = int;

class PlayerControlSystem: public ISystem {
public:
    PlayerControlSystem(Engine* engine);
    ~PlayerControlSystem() override;

    bool onEvent(
        const std::shared_ptr<IEvent>& event) const override;
};

}

#endif // FIREFLY_SYSTEMS_PLAYER_CONTROL_H
