/*
 * Copyright (c) 2022, Roman Meita <theshrodingerscat@gmail.com>
 * All rights reserved
 */

#ifndef FALCON_SYSTEMS_ANIMATION_H
#define FALCON_SYSTEMS_ANIMATION_H

#include <mutex>

#include "ISystem.h"

namespace falcon {

class Renderer;
class Position;
class Visual;

class RenderingSystem: public ISystem {
public:
    RenderingSystem(Engine* engine);
    ~RenderingSystem() override;

    void drawEntites() const;

    bool onEvent(
        const std::shared_ptr<IEvent>& event) const override;

private:
    bool checkComponents(Entity* entity) const override;
    void lockEntities() const override;
    void unlockEntities() const override;

    void draw(Position* positionComponent, 
        Visual* visualComponent) const;

private:
    ComponentID _visualComponentId;
    ComponentID _positionComponentId;
    mutable std::mutex _entityMutex;
    Renderer* const _renderer;
};

}

#endif // FALCON_SYSTEMS_ANIMATION_H
