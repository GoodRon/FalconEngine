#include "IGameState.h"

namespace firefly {

IGameState::IGameState(Engine* engine):
	_engine(engine) {
}

IGameState::~IGameState() {
}

void IGameState::onEnter() {
}

void IGameState::onExit() {
}

bool IGameState::onEvent(
	const std::shared_ptr<IEvent>& event) {
	return false;
}

Engine* IGameState::getEngine() const {
	return _engine;
}

}
