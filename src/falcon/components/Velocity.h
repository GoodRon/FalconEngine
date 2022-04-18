/*
 * Copyright (c) 2022, Roman Meita <theshrodingerscat@gmail.com>
 * All rights reserved
 */

#ifndef FALCON_COMPONENT_VELOCITY_H
#define FALCON_COMPONENT_VELOCITY_H

namespace falcon {

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

#endif // FALCON_COMPONENT_VELOCITY_H
