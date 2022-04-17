/*
 * Copyright (c) 2015, Roman Meyta <theshrodingerscat@gmail.com>
 * All rights reserved
 */

#ifndef FALCON_COMMAND_H
#define FALCON_COMMAND_H

namespace falcon {

class WorldObject;

class Command {
public:
    virtual ~Command() {}
    virtual void execute(WorldObject* object) = 0;
};

}

#endif // FALCON_COMMAND_H
