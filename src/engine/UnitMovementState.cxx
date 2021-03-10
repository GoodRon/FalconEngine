/*
 * Copyright (c) 2015, Roman Meyta <theshrodingerscat@gmail.com>
 * All rights reserved
 */

#include <cmath>

#include <SDL2/SDL.h>

#include "UnitMovementState.h"
#include "UnitIdleState.h"
#include "Unit.h"

namespace falcon {

UnitMovementState::UnitMovementState(int x, int y) :
	State<Unit>(),
	_destinationX(x),
	_destinationY(y),
	_deltaX(0.0),
	_deltaY(0.0),
	_startTime() {

	_startTime = std::chrono::steady_clock::now();
}

UnitMovementState::~UnitMovementState() {
}

void UnitMovementState::onEnter(Unit* object) {
	if (!object) {
		return;
	}
	object->changeAnimation(AnimationType::Movement);
}

//#include <iostream>
void UnitMovementState::doLogic(Unit* object) {
	if (!object) {
		return;
	}
	auto pos = object->getPosition();
	double distance = sqrt((_destinationX - pos.x) * (_destinationX - pos.x) + 
		(_destinationY - pos.y) * (_destinationY - pos.y));

	double deltaX = _destinationX - pos.x;
	double deltaY = _destinationY - pos.y;
	double angle = atan2(deltaY, deltaX) * 180.0 / M_PI;
	object->setDirection(90.0 + angle);

	auto currentTime = std::chrono::steady_clock::now();
	auto deltaTime = std::chrono::duration_cast<std::chrono::milliseconds>(
		currentTime - _startTime);
	_startTime = currentTime;

	double path = object->getSpeed() * deltaTime.count() / 1000.0;
	_deltaX = path * cos(angle * M_PI / 180.0);
	_deltaY = path * sin(angle * M_PI / 180.0);
	double x = pos.x + _deltaX;
	double y = pos.y + _deltaY;
	object->setPosition(x, y);

	/*
	// TODO remove debug!
	cout << "distance: " << distance << " angle " << angle << " path " << path
		 << " dx: " << _deltaX
		 << " dy: " << _deltaY << " angle " << angle << " sin " << sin(angle * M_PI / 180.0)
		 << " cos " << cos(angle * M_PI / 180.0) << endl;
	*/

	if (distance - path < 0.0) {
		std::unique_ptr<State<Unit>> state(new UnitIdleState);
		object->changeState(std::move(state));
	}
}

}
