#include "IGameState.h"

namespace firefly {

IGameState::IGameState(
	Engine* engine, 
	int id):
	_engine(engine),
	_id(id) {
}

IGameState::~IGameState() {
}

void IGameState::onEnter() {
}

void IGameState::onExit() {
}

int IGameState::getId() const {
	return _id;
}

bool IGameState::onEvent(
	const std::shared_ptr<IEvent>& event) {
	return false;
}

Engine* IGameState::getEngine() const {
	return _engine;
}

}
