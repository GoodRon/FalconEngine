/*
 * Copyright (c) 2015, Roman Meyta <theshrodingerscat@gmail.com>
 * All rights reserved
 */

#ifndef UNITMOVECOMMAND_H
#define UNITMOVECOMMAND_H

#include "Command.h"

class UnitMoveCommand : public Command {
public:
	UnitMoveCommand(int x, int y);
    virtual ~UnitMoveCommand();
    virtual void execute(WorldObject* object) override;

private:
	int m_x;
	int m_y;
};

#endif // UNITMOVECOMMAND_H
