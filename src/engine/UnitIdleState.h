/*
 * Copyright (c) 2015, Roman Meyta <theshrodingerscat@gmail.com>
 * All rights reserved
 */

#ifndef FALCON_UNIT_IDLE_STATE_H
#define FALCON_UNIT_IDLE_STATE_H

#include "State.h"

namespace falcon {

class Unit;

class UnitIdleState: public State<Unit> {
public:
	UnitIdleState();

	~UnitIdleState() override;

	virtual void onEnter(Unit* object) override;
};

}

#endif // FALCON_UNIT_IDLE_STATE_H
