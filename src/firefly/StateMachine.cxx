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

bool StateMachine::pushState(int stateId, 
	std::unique_ptr<IGameState>&& state) {

	if (!state || hasState(stateId)) {
		return false;
	}
	_states[stateId] = std::move(state);
}

bool StateMachine::switchState(int stateId) {
	if (hasState(stateId)) {
		return false;
	}

	_states[_currentStateId]->onExit();
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

bool StateMachine::onEvent(
	const std::shared_ptr<firefly::IEvent>& event) {

	if (_currentStateId < 0) {
		return false;
	}

	return _states[_currentStateId]->onEvent(event);
}

}
