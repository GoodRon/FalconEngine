/*
 * Copyright (c) 2015, Roman Meyta <theshrodingerscat@gmail.com>
 * All rights reserved
 */

#include "UnitMovementState.h"
#include "Unit.h"

UnitMovementState::UnitMovementState() :
	State<Unit>() {
}

UnitMovementState::~UnitMovementState() {

}

void UnitMovementState::onEnter(Unit* object) {
	if (!object) {
		return;
	}
	object->changeAnimation(atMovement);
}

void UnitMovementState::onExit(Unit* object) {

}

void UnitMovementState::doLogic(Unit* object) {

}
