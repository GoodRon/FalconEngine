/*
 * Copyright (c) 2022, Roman Meita <theshrodingerscat@gmail.com>
 * All rights reserved
 */

#ifndef FIREFLY_COMPONENT_VISUAL_H
#define FIREFLY_COMPONENT_VISUAL_H

#include <unordered_map>

#include "IComponent.h"

namespace firefly {

class Frame;

class Visual: public IComponent {
public:
    inline static const std::string ComponentName = "Visual";

    Visual(): IComponent(ComponentName) {}
    ~Visual() override = default;

    using StateName = std::string;
    using Direction = int;
    using Frames = std::vector<std::shared_ptr<Frame>>;
	
    struct State {
        std::unordered_map<Direction, Frames> frames;
        bool isLooped = true;
    };

    StateName currentState = "Idle";
    Direction currentDirection = 0;
    size_t frameIndex = 0; 
    std::unordered_map<StateName, State> states;
    bool isPaused = false;
    bool isVisible = false;
    int zIndex = 0;
};

}

#endif // FIREFLY_COMPONENT_VISUAL_H
