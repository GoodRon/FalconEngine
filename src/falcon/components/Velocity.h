/*
 * Copyright (c) 2022, Roman Meita <theshrodingerscat@gmail.com>
 * All rights reserved
 */

#ifndef FALCON_COMPONENT_VELOCITY_H
#define FALCON_COMPONENT_VELOCITY_H

namespace falcon {

class Velocity: public IComponent {
public:
    Velocity(): IComponent("Velocity"), x(0), y(0) {}
    
    std::shared_ptr<IComponent> clone() const override {
        return std::shared_ptr<IComponent>(new Velocity);
    }

    int x;
    int y;
};

}

#endif // FALCON_COMPONENT_VELOCITY_H
