/*
 * Copyright (c) 2022, Roman Meita <theshrodingerscat@gmail.com>
 * All rights reserved
 */

#ifndef FIREFLY_SYSTEMS_ANIMATION_H
#define FIREFLY_SYSTEMS_ANIMATION_H

#include <mutex>

#include "ISystem.h"

namespace firefly {

class Renderer;
class Position;
class Visual;

class RenderingSystem final: public ISystem {
public:
    RenderingSystem(Engine* engine);
    ~RenderingSystem() override;

    RenderingSystem(const RenderingSystem&) = delete;
    RenderingSystem& operator=(const RenderingSystem&) = delete;

    void drawEntites() const;

    bool onEvent(
        const std::shared_ptr<IEvent>& event) override;

private:
    void lockEntities() const override;
    void unlockEntities() const override;

    void draw(Position* positionComponent, 
        Visual* visualComponent) const;

private:
    mutable std::mutex _entityMutex;
    Renderer* const _renderer;
};

}

#endif // FIREFLY_SYSTEMS_ANIMATION_H