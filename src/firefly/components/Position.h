/*
 * Copyright (c) 2022, Roman Meita <theshrodingerscat@gmail.com>
 * All rights reserved
 */

#ifndef FIREFLY_COMPONENT_POSITION_H
#define FIREFLY_COMPONENT_POSITION_H

#include "IComponent.h"

namespace firefly {

class Position: public IComponent {
public:
    inline static const std::string ComponentName = "Position";
    
    Position(): IComponent(ComponentName) {}
    ~Position() override = default;

    SDL_Rect toRect() {
        return SDL_Rect{x, y, 
            static_cast<int>(width * scale), 
            static_cast<int>(height * scale)};
    }

	int x = 0;
	int y = 0;
    int width = 0;
    int height = 0;
    double scale = 0.0;
};

}

#endif // FIREFLY_COMPONENT_POSITION_H
