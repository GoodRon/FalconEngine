#include "StateMachine.h"

#include "IGameState.h"

namespace firefly {

StateMachine::StateMachine():
	_currentStateId(-1),
	_states() {
}

StateMachine::~StateMachine() {
	if (_currentStateId >= 0) {
		_states[_currentStateId]->onExit();
	}
}

bool StateMachine::pushState(
	std::unique_ptr<IGameState>&& state) {

	if (!state) {
		return false;
	}

	const int id = state->getId();
	if (hasState(id)) {
		return false;
	}
	_states[id] = std::move(state);
	return true;
}

bool StateMachine::switchState(int stateId) {
	if (!hasState(stateId)) {
		return false;
	}

	if (hasState(_currentStateId)) {
		_states[_currentStateId]->onExit();
	}

	_currentStateId = stateId;
	_states[_currentStateId]->onEnter();
	return true;
}

void StateMachine::clearStates() {
	_currentStateId = -1;
	_states.clear();
}

bool StateMachine::hasState(int stateId) const {
	if (_states.find(stateId) == _states.end()) {
		return false;
	}
	return true;
}

bool StateMachine::processEvent(
	const std::shared_ptr<firefly::IEvent>& event) {

	if (_currentStateId < 0) {
		return false;
	}
	return _states[_currentStateId]->onEvent(event);
}

}