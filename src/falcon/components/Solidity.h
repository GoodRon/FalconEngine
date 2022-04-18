/*
 * Copyright (c) 2022, Roman Meita <theshrodingerscat@gmail.com>
 * All rights reserved
 */

#ifndef FALCON_COMPONENT_SOLIDITY_H
#define FALCON_COMPONENT_SOLIDITY_H

#include "IComponent.h"

namespace falcon {

class Solidity: public IComponent final {
public:
    inline static const std::string ComponentName = "Solidity";
    
    Solidity(): IComponent(ComponentName) {}
    ~Solidity() override = default;

	bool isSolid = false;
    bool isDestructable = false;
    // collision box
};

}

#endif // FALCON_COMPONENT_SOLIDITY_H
