/*
 * Copyright (c) 2022, Roman Meita <theshrodingerscat@gmail.com>
 * All rights reserved
 */

#ifndef FIREFLY_COMPONENT_VELOCITY_H
#define FIREFLY_COMPONENT_VELOCITY_H

namespace firefly {

class Velocity final: public IComponent {
public:
    inline static const std::string ComponentName = "Velocity";
    
    Velocity(): IComponent(ComponentName) {}
    ~Velocity() override = default;

    int speedX = 0;
    int speedY = 0;
    int accelerationX = 0;
    int accelerationY = 0;
};

}

#endif // FIREFLY_COMPONENT_VELOCITY_H
