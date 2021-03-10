/*
 * Copyright (c) 2015, Roman Meyta <theshrodingerscat@gmail.com>
 * All rights reserved
 */

#ifndef FALCON_UNIT_MOVEMENT_STATE_H
#define FALCON_UNIT_MOVEMENT_STATE_H

#include <chrono>

#include "State.h"

namespace falcon {

class Unit;

class UnitMovementState : public State<Unit> {
public:
	UnitMovementState(int x, int y);

	virtual ~UnitMovementState();

	virtual void onEnter(Unit* object) override;

	virtual void doLogic(Unit* object) override;

private:
	int _destinationX;
	int _destinationY;
	double _deltaX;
	double _deltaY;
	std::chrono::steady_clock::time_point _startTime;
};

}

#endif // FALCON_UNIT_MOVEMENT_STATE_H
