/*
 * Copyright (c) 2022, Roman Meita <theshrodingerscat@gmail.com>
 * All rights reserved
 */

#ifndef FIREFLY_COMPONENT_VELOCITY_H
#define FIREFLY_COMPONENT_VELOCITY_H

#include "IComponent.h"

namespace firefly {

class Velocity final: public IComponent {
public:
    inline static const std::string ComponentName = "Velocity";
    
    Velocity(): IComponent(ComponentName) {}
    ~Velocity() override = default;

    // TODO improve
    double speedX = 0.0;
    double speedY = 0.0;
    double accelerationX = 0.0;
    double accelerationY = 0.0;
    //double maxSpeed = 0.0;
};

}

#endif // FIREFLY_COMPONENT_VELOCITY_H
