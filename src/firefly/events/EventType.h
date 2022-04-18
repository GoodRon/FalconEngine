/*
 * Copyright (c) 2022, Roman Meita <theshrodingerscat@gmail.com>
 * All rights reserved
 */

#ifndef FIREFLY_EVENT_TYPE_H
#define FIREFLY_EVENT_TYPE_H

namespace firefly {

enum class EventType: int {
    Unknown = 0,
    NativeEvent,
    UpdateLogic,
    Render,
    Collide,
    Destroy,
};

}

#endif // FIREFLY_EVENT_TYPE_H
