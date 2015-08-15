/*
 * Copyright (c) 2015, Roman Meyta <theshrodingerscat@gmail.com>
 * All rights reserved
 */

#ifndef UNIT_H
#define UNIT_H

#include "WorldObject.h"

class State;
class StateMachine;

/**
 * @brief Класс юнита
 */
class Unit : public WorldObject {
public:
	Unit();

	virtual ~Unit();

	virtual void doLogic();

	virtual void draw(Renderer* renderer);

	void moveTo(int x, int y);
	void attack(WorldObject& object);

	void changeState(State* state);

private:
	/**
	 * @brief Машина состояний
	 */
	StateMachine<Unit>* m_stateMachine;
};

#endif // UNIT_H
