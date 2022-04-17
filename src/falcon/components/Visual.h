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

    using StateName = std::string;
    using Direction = int;
    using Frames = std::vector<std::shared_ptr<Frame>>;
	
    struct State {
        std::unordered_map<Direction, Frames> frames;
        bool isLooped = true;
    };

    StateName currentState;
    Direction currentDirection = 0;
    size_t frameIndex = 0; 
    std::unordered_map<StateName, State> states;
    bool isPaused = false;
    bool isVisible = false;
    int zIndex = 0;
};

}

#endif // FALCON_COMPONENT_VISUAL_H
