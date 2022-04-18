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
    inline static const std::string ComponentName = "Player";
    
    Player(): IComponent(ComponentName) {}
    ~Player() override = default;

	int playerId = 0;
};

}

#endif // FALCON_COMPONENT_CONTROL_H
