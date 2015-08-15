/*
 * Copyright (c) 2015, Roman Meyta <theshrodingerscat@gmail.com>
 * All rights reserved
 */

#include "Unit.h"
#include "StateMachine.h"

Unit::Unit(): m_stateMachine(new StateMachine<Unit>(this)) {
}

Unit::~Unit() {
}

void Unit::doLogic() {

}

void Unit::draw(Renderer* renderer) {

}

void Unit::moveTo(int x, int y) {

}

void Unit::attack(WorldObject& object) {

}

void Unit::changeState(State<Unit>* state) {

}
