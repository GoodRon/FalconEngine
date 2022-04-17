/*
 * Copyright (c) 2022, Roman Meita <theshrodingerscat@gmail.com>
 * All rights reserved
 */

#ifndef FALCON_SYSTEMS_ANIMATION_H
#define FALCON_SYSTEMS_ANIMATION_H

#include "ISystem.h"

namespace falcon {

using ComponentID = int;

class RenderingSystem: public ISystem {
public:
    RenderingSystem();
    ~RenderingSystem() override;

    bool onEvent(
        const std::shared_ptr<IEvent>& event) const override;

private:
    bool checkComponents(Entity* entity) const override;

private:
    ComponentID _visualComponentId;
};

}

#endif // FALCON_SYSTEMS_ANIMATION_H
