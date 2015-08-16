/*
 * Copyright (c) 2015, Roman Meyta <theshrodingerscat@gmail.com>
 * All rights reserved
 */

#include "Unit.h"
#include "StateMachine.h"
#include "UnitIdleState.h"

Unit::Unit():
	m_stateMachine(new StateMachine<Unit>(this)),
	m_currentAnimation(nullptr),
	m_animations(),
	m_direction(0.0) {
	m_stateMachine->setCurrentState(new UnitIdleState);
}

Unit::~Unit() {
}

void Unit::setAnimation(AnimationType type, const AnimationPointer& animation) {
	m_animations[type] = animation;
}

void Unit::doLogic() {
	if (!m_stateMachine) {
		return;
	}
	m_stateMachine->updateState();
}

void Unit::draw(Renderer* renderer) {
	if (!m_currentAnimation) {
		return;
	}


}

void Unit::moveTo(int x, int y) {

}

void Unit::attack(WorldObject& object) {

}

void Unit::changeState(State<Unit>* state) {
	if (!m_stateMachine) {
		return;
	}
	m_stateMachine->changeState(state);
}
