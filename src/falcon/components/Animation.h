/*
 * Copyright (c) 2022, Roman Meita <theshrodingerscat@gmail.com>
 * All rights reserved
 */

#ifndef FALCON_COMPONENT_ANIMATION_H
#define FALCON_COMPONENT_ANIMATION_H

#include <unordered_map>

#include "IComponent.h"
#include "Frame.h"

namespace falcon {

class Animation: public IComponent {
public:
    Animation(): IComponent("Animation"), 
        states(), currentState(0), currentFrame(0),
        isPaused(true), isLooped(false) {}

    std::shared_ptr<IComponent> clone() const override {
        return std::shared_ptr<IComponent>(new Animation);
    }

    using State = int;
    using Direction = int;
    using Frames = std::vector<Frame>;
    using AnimatedState = std::unordered_map<Direction, Frames>;
	
    std::unordered_map<State, AnimatedState> states;
    State currentState;
    size_t currentFrame;
    bool isPaused;
    bool isLooped;
};

}

#endif // FALCON_COMPONENT_ANIMATION_H
