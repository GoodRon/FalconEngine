/*
 * Copyright (c) 2015, Roman Meyta <theshrodingerscat@gmail.com>
 * All rights reserved
 */

#include <cmath>

#include <SDL2/SDL.h>

#include "UnitMovementState.h"
#include "UnitIdleState.h"
#include "Unit.h"

using namespace std;
using namespace chrono;

UnitMovementState::UnitMovementState(int x, int y) :
	State<Unit>(),
	m_destinationX(x),
	m_destinationY(y),
	m_deltaX(0.0),
	m_deltaY(0.0),
	m_startTime() {
	m_startTime = steady_clock::now();
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

#include <iostream>
void UnitMovementState::doLogic(Unit* object) {
	if (!object) {
		return;
	}
	auto pos = object->getPosition();
	double distance = sqrt((m_destinationX - pos.x) * (m_destinationX - pos.x) + 
		(m_destinationY - pos.y) * (m_destinationY - pos.y));

	auto deltaX = m_destinationX - pos.x;
	auto deltaY = m_destinationY - pos.y;
	auto angle = 90.0 - atan(deltaY/deltaX);

	auto currentTime = steady_clock::now();
	auto deltaTime = duration_cast<milliseconds>(currentTime - m_startTime);
	m_startTime = currentTime;

	double path = object->getSpeed() * deltaTime.count() / 1000.0;
	m_deltaX = path * sin(angle);
	m_deltaY = path * cos(angle);
	double x = pos.x + m_deltaX;
	double y = pos.y + m_deltaY;
	object->setPosition(x, y);

	cout << "distance: " << distance << " path " << path << " dx: " << m_deltaX 
		 << " dy: " << m_deltaY << " angle " << angle << " sin " << sin(angle) 
		 << " cos " << cos(angle) << endl;

	if (distance - path < 0.0) {
		object->changeState(new UnitIdleState);
	}
}
