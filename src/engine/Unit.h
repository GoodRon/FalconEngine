/*
 * Copyright (c) 2015, Roman Meyta <theshrodingerscat@gmail.com>
 * All rights reserved
 */

#ifndef FALCON_UNIT_H
#define FALCON_UNIT_H

#include <map>
#include <memory>

#include "WorldObject.h"
#include "StateMachine.h"
#include "AnimationTypes.h"

namespace falcon {

class IAnimation;
class Command;

using AnimationPointer = std::shared_ptr<IAnimation>;

class Unit: public WorldObject {
public:
	Unit();

	~Unit() override;

	void doLogic() override;

	void draw(Renderer* renderer) override;

	void executeCommand(Command* command) override;

	void setSpeed(double speed);
	double getSpeed() const;

	void setAnimation(AnimationType type, const AnimationPointer& animation);
	void setDirection(double direction);

	void setScale(double scale);

	virtual void moveTo(int x, int y);

	virtual void attack(WorldObject& object);

	void changeState(std::unique_ptr<State<Unit>>&& state);

	void backToPreviousState();

	void changeAnimation(AnimationType type);

private:
	std::unique_ptr<StateMachine<Unit>> _stateMachine;
	AnimationPointer _currentAnimation;
	std::map<AnimationType, AnimationPointer> _animations;
	double _direction;
	double _speed;
	double _scale;
};

}

#endif // FALCON_UNIT_H
