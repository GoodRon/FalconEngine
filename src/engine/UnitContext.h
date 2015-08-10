/*
 * Copyright (c) 2015, Roman Meyta <theshrodingerscat@gmail.com>
 * All rights reserved
 */

#ifndef UNITCONTEXT_H
#define UNITCONTEXT_H

class UnitState;

class UnitContext {
public:
	UnitContext();
	~UnitContext();



public:
	UnitState* m_state;
};

#endif // UNITCONTEXT_H
