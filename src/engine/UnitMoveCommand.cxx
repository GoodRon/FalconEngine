/*
 * Copyright (c) 2015, Roman Meyta <theshrodingerscat@gmail.com>
 * All rights reserved
 */

#include "UnitMoveCommand.h"
#include "Unit.h"

UnitMoveCommand::UnitMoveCommand(int x, int y):
	Command(),
	m_x(x),
	m_y(y) {
}

UnitMoveCommand::~UnitMoveCommand() {
}

void UnitMoveCommand::execute(WorldObject* object) {
	auto unit = dynamic_cast<Unit*>(object);
	if (unit == nullptr) {
		return;
	}
	unit->moveTo(m_x, m_y);
}
