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
    Visual(): IComponent("Visual") {}
    ~Visual() override = default;

    using State = std::string;
    using Direction = int;
    using Frames = std::vector<std::shared_ptr<Frame>>;
    using AnimatedState = std::unordered_map<Direction, Frames>;
	
    size_t frameIndex = 0;
    Direction currentDirection = 0;
    State currentState;
    std::unordered_map<State, AnimatedState> states;
    bool isPaused = false;
    bool isLooped = true;
    bool isVisible = false;
    int zIndex = 0;
};

}

#endif // FALCON_COMPONENT_VISUAL_H
