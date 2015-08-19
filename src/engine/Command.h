/*
 * Copyright (c) 2015, Roman Meyta <theshrodingerscat@gmail.com>
 * All rights reserved
 */

#ifndef COMMAND_H
#define COMMAND_H

class WorldObject;

class Command {
public:
    virtual ~Command() {}
    virtual void execute(WorldObject* object) = 0;
};

#endif // COMMAND_H
