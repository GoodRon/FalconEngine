/*
 * Copyright (c) 2015, Roman Meyta <theshrodingerscat@gmail.com>
 * All rights reserved
 */

#include "UnitIdleState.h"
#include "Unit.h"

UnitIdleState::UnitIdleState() :
	State<Unit>() {
}

UnitIdleState::~UnitIdleState() {

}

void UnitIdleState::onEnter(Unit* object) {
	if (!object) {
		return;
	}
	object->changeAnimation(atIdle);
}

void UnitIdleState::onExit(Unit* object) {

}

void UnitIdleState::doLogic(Unit* object) {

}
