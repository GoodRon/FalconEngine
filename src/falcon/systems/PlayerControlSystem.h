/*
 * Copyright (c) 2022, Roman Meita <theshrodingerscat@gmail.com>
 * All rights reserved
 */

#ifndef FALCON_SYSTEMS_PLAYER_CONTROL_H
#define FALCON_SYSTEMS_PLAYER_CONTROL_H

#include "ISystem.h"

namespace falcon {

using ComponentID = int;

class PlayerControlSystem: public ISystem {
public:
    PlayerControlSystem();
    ~PlayerControlSystem() override;

    bool resolveComponentIDs(
        ComponentRegistry* componentRegistry) override;

    bool onEvent(
        const std::shared_ptr<IEvent>& event) const override;

private:
    bool checkComponents(Entity* entity) const override;

private:
    ComponentID _playerComponentId;
};

}

#endif // FALCON_SYSTEMS_PLAYER_CONTROL_H
