/*
 * Copyright (c) 2015, Roman Meyta <theshrodingerscat@gmail.com>
 * All rights reserved
 */

#ifndef UNIT_H
#define UNIT_H

#include "WorldObject.h"

class UnitState {
public:

private:

};

class Unit : public WorldObject {
public:
	Unit();

	virtual ~Unit();

	virtual void doLogic();

private:
	double m_direction;
};

#endif // UNIT_H
