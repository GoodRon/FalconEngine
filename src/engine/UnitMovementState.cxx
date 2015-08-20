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

	double deltaX = m_destinationX - pos.x;
	double deltaY = m_destinationY - pos.y;
	double angle = atan2(deltaY, deltaX) * 180.0 / M_PI;
	object->setDirection(90.0 + angle);

	auto currentTime = steady_clock::now();
	auto deltaTime = duration_cast<milliseconds>(currentTime - m_startTime);
	m_startTime = currentTime;

	double path = object->getSpeed() * deltaTime.count() / 1000.0;
	m_deltaX = path * cos(angle * M_PI / 180.0);
	m_deltaY = path * sin(angle * M_PI / 180.0);
	double x = pos.x + m_deltaX;
	double y = pos.y + m_deltaY;
	object->setPosition(x, y);

	cout << "distance: " << distance << " angle " << angle << " path " << path
		 << " dx: " << m_deltaX
		 << " dy: " << m_deltaY << " angle " << angle << " sin " << sin(angle * M_PI / 180.0)
		 << " cos " << cos(angle * M_PI / 180.0) << endl;

	if (distance - path < 0.0) {
		object->changeState(new UnitIdleState);
	}
}
