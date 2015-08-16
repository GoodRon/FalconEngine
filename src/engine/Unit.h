/*
 * Copyright (c) 2015, Roman Meyta <theshrodingerscat@gmail.com>
 * All rights reserved
 */

#ifndef UNIT_H
#define UNIT_H

#include <map>

#include "WorldObject.h"
#include "StateMachine.h"
#include "AnimationTypes.h"

class IAnimation;

/**
 * @brief Класс юнита
 */
class Unit : public WorldObject {
public:
	// TODO сделать загрузку из json
	Unit();

	virtual ~Unit();

	// временно, пока не реализован нормальный конструктор или фабрика
	void setAnimation(AnimationType type, IAnimation* animation);

	virtual void doLogic();

	virtual void draw(Renderer* renderer);

	virtual void moveTo(int x, int y);

	// добавить параметр weapon
	virtual void attack(WorldObject& object);

	void changeState(State<Unit>* state);

	void changeAnimation(AnimationType type);

private:
	virtual double calculateDistance(const WorldObject& object) const;

private:
	/**
	 * @brief Машина состояний
	 */
	StateMachine<Unit>* m_stateMachine;

	IAnimation* m_currentAnimation;

	std::map<AnimationType, IAnimation*> m_animations;

	double m_direction;
};

#endif // UNIT_H
