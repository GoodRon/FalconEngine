/*
 * Copyright (c) 2015, Roman Meyta <theshrodingerscat@gmail.com>
 * All rights reserved
 */

#include <SDL2/SDL.h>

#include "Unit.h"
#include "UnitIdleState.h"
#include "Renderer.h"

Unit::Unit():
	m_stateMachine(new StateMachine<Unit>(this)),
	m_currentAnimation(),
	m_animations(),
	m_direction(0.0) {
	m_stateMachine->setCurrentState(new UnitIdleState);
}

Unit::~Unit() {
}

void Unit::setAnimation(AnimationType type, const AnimationPointer& animation) {
	m_animations[type] = animation;
}

void Unit::setDirection(double direction) {
	direction = fmod(direction, 360.0);
	if (direction < 0.0) {
		direction += 360.0;
	}
	m_direction = direction;
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

	auto frame = m_currentAnimation->getFrame(m_direction);
	// TODO забирать через интерфейс анимации
	SDL_Rect source = {0, 0, 0, 0};
	SDL_QueryTexture(frame.get(), nullptr, nullptr, &(source.w), &(source.h));
	SDL_Rect dest = {0, 0, source.w, source.h};
	renderer->drawTexture(frame, &source, &dest);
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

void Unit::changeAnimation(AnimationType type) {
	if (m_animations.find(type) != m_animations.end()) {
		m_currentAnimation = m_animations[type];
		m_currentAnimation->play(true);
	}
}
