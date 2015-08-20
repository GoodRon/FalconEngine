/*
 * Copyright (c) 2015, Roman Meyta <theshrodingerscat@gmail.com>
 * All rights reserved
 */

#ifndef UNITMOVEMENTSTATE_H
#define UNITMOVEMENTSTATE_H

#include <chrono>

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
	UnitMovementState(int x, int y);

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

private:
	int m_destinationX;
	int m_destinationY;
	double m_deltaX;
	double m_deltaY;
	std::chrono::steady_clock::time_point m_startTime;
};

#endif // UNITMOVEMENTSTATE_H
