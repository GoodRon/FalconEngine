/*
 * Copyright (c) 2022, Roman Meita <theshrodingerscat@gmail.com>
 * All rights reserved
 */

#ifndef FIREFLY_SYSTEMS_POSITIONING_H
#define FIREFLY_SYSTEMS_POSITIONING_H

#include "ISystem.h"

namespace firefly {

class Position;
class Velocity;

class PositioningSystem final: public ISystem {
public:
    PositioningSystem(Engine* engine);
    ~PositioningSystem() override;

    PositioningSystem(const PositioningSystem&) = delete;
    PositioningSystem& operator=(const PositioningSystem&) = delete;

    void update() override;

    bool onEvent(
        const std::shared_ptr<IEvent>& event) override;

private:
    void processPosition(
        Position* position, Velocity* velocity, 
        uint64_t elapsedMs) const;
};

}

#endif // FIREFLY_SYSTEMS_POSITIONING_H
