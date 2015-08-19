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
#include "IAnimation.h"

class IAnimation;
class Command;

/**
 * @brief Умный указатель на объект анимации
 */
typedef std::shared_ptr<IAnimation> AnimationPointer;

/**
 * @brief Класс юнита
 */
class Unit : public WorldObject {
public:
	// TODO сделать загрузку из json 
	Unit();

	virtual ~Unit();

	virtual void doLogic() override;

	virtual void draw(Renderer* renderer) override;

	virtual void executeCommand(Command* command) override;

	void setSpeed(double speed);

	double getSpeed() const;

	// временно, пока не реализован нормальный конструктор или фабрика
	void setAnimation(AnimationType type, const AnimationPointer& animation);
	// временно,
	void setDirection(double direction);

	virtual void moveTo(int x, int y);

	// добавить параметр weapon
	virtual void attack(WorldObject& object);

	void changeState(State<Unit>* state);

	void backToPreviousState();

	void changeAnimation(AnimationType type);

private:
	/**
	 * @brief Машина состояний
	 */
	StateMachine<Unit>* m_stateMachine;

	/**
	 * @brief Текущая анимация
	 */
	AnimationPointer m_currentAnimation;

	/**
	 * @brief Мэп анимаций
	 */
	std::map<AnimationType, AnimationPointer> m_animations;

	/**
	 * @brief Направление
	 */
	double m_direction;

	double m_speed;

	// weapon/item с приоритетом отрисовки в зависимости от направления
	// инвентарь
	// контроллер для управления персонажем
};

#endif // UNIT_H
