/*
 * Copyright (c) 2015, Roman Meyta <theshrodingerscat@gmail.com>
 * All rights reserved
 */

#include <SDL.h>

#include "Unit.h"
#include "UnitIdleState.h"
#include "UnitMovementState.h"
#include "Renderer.h"
#include "Command.h"
#include "IAnimation.h"

namespace falcon {

Unit::Unit():
	_stateMachine(new StateMachine<Unit>(this)),
	_currentAnimation(),
	_animations(),
	_direction(0.0),
	_speed(10.0),
	_scale(1.0) {

	std::unique_ptr<State<Unit>> state(new UnitIdleState);
	_stateMachine->setCurrentState(std::move(state));
}

Unit::~Unit() {
}

void Unit::doLogic() {
	if (!_stateMachine) {
		return;
	}
	_stateMachine->updateState();
}

void Unit::draw(Renderer* renderer) {
	if (!_currentAnimation) {
		return;
	}

	auto frame = _currentAnimation->getFrame(_direction);

	SDL_Rect source = {0, 0, 0, 0};
	SDL_QueryTexture(frame.get(), nullptr, nullptr, &(source.w), &(source.h));
	SDL_Rect dest = {_x, _y, static_cast<int>(source.w * _scale),
					 static_cast<int>(source.h * _scale)};
	renderer->drawTexture(frame, &source, &dest);
}

void Unit::executeCommand(Command* command) {
	if (command == nullptr) {
		return;
	}
	command->execute(this);
}

void Unit::setSpeed(double speed) {
	_speed = speed;
}

double Unit::getSpeed() const {
	return _speed;
}

void Unit::setAnimation(AnimationType type, const AnimationPointer& animation) {
	_animations[type] = animation;
}

void Unit::setDirection(double direction) {
	direction = fmod(direction, 360.0);
	if (direction < 0.0) {
		direction += 360.0;
	}
	_direction = direction;
}

void Unit::setScale(double scale) {
	_scale = scale;
}

void Unit::moveTo(int x, int y) {
	std::unique_ptr<State<Unit>> state(new UnitMovementState(x, y));

	changeState(std::move(state));
}

void Unit::attack(WorldObject& object) {

}

void Unit::changeState(std::unique_ptr<State<Unit>>&& state) {
	if (!_stateMachine) {
		return;
	}
	_stateMachine->changeState(std::move(state));
}

void Unit::backToPreviousState() {
	if (!_stateMachine) {
		return;
	}
	_stateMachine->backToPreviousState();
}

void Unit::changeAnimation(AnimationType type) {
	if (_animations.find(type) != _animations.end()) {
		_currentAnimation = _animations[type];
		_currentAnimation->play();
	}
}

}
