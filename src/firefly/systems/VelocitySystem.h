/*
 * Copyright (c) 2022, Roman Meita <theshrodingerscat@gmail.com>
 * All rights reserved
 */

#ifndef FIREFLY_SYSTEMS_VELOCITY_H
#define FIREFLY_SYSTEMS_VELOCITY_H

#include "ISystem.h"

namespace firefly {

class Velocity;

class VelocitySystem final: public ISystem {
public:
    VelocitySystem(Engine* engine);
    ~VelocitySystem() override;

    VelocitySystem(const VelocitySystem&) = delete;
    VelocitySystem& operator=(const VelocitySystem&) = delete;

    void update() override;

    bool onEvent(
        const std::shared_ptr<IEvent>& event) override;

private:
    void processVelocity(Velocity* velocity) const;
};

}

#endif // FIREFLY_SYSTEMS_VELOCITY_H
