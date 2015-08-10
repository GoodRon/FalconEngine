/*
 * Copyright (c) 2015, Roman Meyta <theshrodingerscat@gmail.com>
 * All rights reserved
 */

#ifndef UNITSTATE_H
#define UNITSTATE_H

class DirectedAnimation;

class UnitState {
public:
	UnitState();
	virtual ~UnitState();

private:
	DirectedAnimation* m_animation;
};

#endif // UNITSTATE_H
