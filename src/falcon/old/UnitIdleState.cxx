/*
 * Copyright (c) 2015, Roman Meyta <theshrodingerscat@gmail.com>
 * All rights reserved
 */

#include "UnitIdleState.h"
#include "Unit.h"

namespace falcon {

UnitIdleState::UnitIdleState() :
	State<Unit>() {
}

UnitIdleState::~UnitIdleState() {
}

void UnitIdleState::onEnter(Unit* object) {
	if (!object) {
		return;
	}
	object->changeAnimation(AnimationType::Idle);
}

}
