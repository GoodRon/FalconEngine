/*
 * Copyright (c) 2015, Roman Meyta <theshrodingerscat@gmail.com>
 * All rights reserved
 */

#ifndef UNITIDLESTATE_H
#define UNITIDLESTATE_H

#include "State.h"

class Unit;

/**
 * @brief Состояние простоя для класса Unit
 */
class UnitIdleState : public State<Unit> {
public:
	/**
	 * @brief Конструктор
	 */
	UnitIdleState();

	/**
	 * @overload
	 */
	virtual ~UnitIdleState();

	/**
	 * @overload
	 */
	virtual void onEnter(Unit* object) override;

	/**
	 * @overload
	 */
	virtual void onExit(Unit* object) override;

	/**
	 * @overload
	 */
	virtual void doLogic(Unit* object) override;
};

#endif // UNITIDLESTATE_H
