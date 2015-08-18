/*
 * Copyright (c) 2015, Roman Meyta <theshrodingerscat@gmail.com>
 * All rights reserved
 */

#ifndef UNITMOVEMENTSTATE_H
#define UNITMOVEMENTSTATE_H

#include "State.h"

class Unit;

/**
 * @brief Состояние простоя для класса Unit
 */
class UnitMovementState : public State<Unit> {
public:
	/**
	 * @brief Конструктор
	 */
	UnitMovementState();

	/**
	 * @overload
	 */
	virtual ~UnitMovementState();

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

#endif // UNITMOVEMENTSTATE_H
