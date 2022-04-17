/*
 * Copyright (c) 2022, Roman Meita <theshrodingerscat@gmail.com>
 * All rights reserved
 */

#ifndef FALCON_COMPONENT_VISUAL_H
#define FALCON_COMPONENT_VISUAL_H

#include <unordered_map>

#include "IComponent.h"

namespace falcon {

class Frame;

class Visual: public IComponent {
public:
    Visual(): IComponent("Visual"), 
        currentFrame(), frameIndex(0), currentState(0), states(),
        isPaused(true), isLooped(false), isVisible(false), zIndex(0) {}

    std::unique_ptr<IComponent> clone() const override {
        return std::unique_ptr<IComponent>(new Visual);
    }

    using State = int;
    using Direction = int;
    using Frames = std::vector<std::shared_ptr<Frame>>;
    using AnimatedState = std::unordered_map<Direction, Frames>;
	
    std::shared_ptr<Frame> currentFrame;
    size_t frameIndex;
    State currentState;
    std::unordered_map<State, AnimatedState> states;
    bool isPaused;
    bool isLooped;
    bool isVisible;
    int zIndex;
};

}

#endif // FALCON_COMPONENT_VISUAL_H
