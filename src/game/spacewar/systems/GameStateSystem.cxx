#include "GameStateSystem.h"

namespace spacewar {

GameSystem::GameSystem(firefly::Engine* engine):
	_currentStateId(-1),
	_states() {

}

GameSystem::~GameSystem() {

}

bool GameSystem::registerState(
	int stateId, const std::unique_ptr<IGameState>& state) {

}

bool GameSystem::switchState(int stateId) {

}

void GameSystem::clearStates() {

}

bool GameSystem::onEvent(
	const std::shared_ptr<firefly::IEvent>& event) {

}

void GameSystem::onUpdate() {

}

}
