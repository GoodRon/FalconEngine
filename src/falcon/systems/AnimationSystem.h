/*
 * Copyright (c) 2022, Roman Meita <theshrodingerscat@gmail.com>
 * All rights reserved
 */

#ifndef FALCON_SYSTEMS_ANIMATION_H
#define FALCON_SYSTEMS_ANIMATION_H

#include "ISystem.h"

namespace falcon {

using ComponentID = int;

class AnimationSystem: public ISystem {
public:
    AnimationSystem();
    ~AnimationSystem() override;

    bool resolveComponentIDs(
        ComponentRegistry* componentRegistry) override;

    bool onEvent(
        const std::shared_ptr<IEvent>& event) const override;

private:
    bool checkComponents(IEntity* entity) const override;

private:
    ComponentID _animationComponentId;
};

}

#endif // FALCON_SYSTEMS_ANIMATION_H
