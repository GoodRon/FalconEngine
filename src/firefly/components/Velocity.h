/*
 * Copyright (c) 2022, Roman Meita <theshrodingerscat@gmail.com>
 * All rights reserved
 */

#ifndef FIREFLY_COMPONENT_VELOCITY_H
#define FIREFLY_COMPONENT_VELOCITY_H

namespace firefly {

class Velocity: public IComponent final {
public:
    inline static const std::string ComponentName = "Velocity";
    
    Velocity(): IComponent(ComponentName) {}
    ~Velocity() override = default;

    int x = 0;
    int y = 0;
    // acceleration?
};

}

#endif // FIREFLY_COMPONENT_VELOCITY_H
