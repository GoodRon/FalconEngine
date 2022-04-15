/*
 * Copyright (c) 2015, Roman Meyta <theshrodingerscat@gmail.com>
 * All rights reserved
 */

#ifndef FALCON_UNIT_MOVE_COMMAND_H
#define FALCON_UNIT_MOVE_COMMAND_H

#include "Command.h"

namespace falcon {

class UnitMoveCommand: public Command {
public:
	UnitMoveCommand(int x, int y);
    ~UnitMoveCommand() override;

    void execute(WorldObject* object) override;

private:
	int _x;
	int _y;
};

}

#endif // FALCON_UNIT_MOVE_COMMAND_H
