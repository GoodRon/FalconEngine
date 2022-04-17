/*
 * Copyright (c) 2015, Roman Meyta <theshrodingerscat@gmail.com>
 * All rights reserved
 */

#include "UnitMoveCommand.h"
#include "Unit.h"

namespace falcon {

UnitMoveCommand::UnitMoveCommand(int x, int y):
	Command(),
	_x(x),
	_y(y) {
}

UnitMoveCommand::~UnitMoveCommand() {
}

void UnitMoveCommand::execute(WorldObject* object) {
	auto unit = dynamic_cast<Unit*>(object);
	if (!unit) {
		return;
	}
	unit->moveTo(_x, _y);
}

}
