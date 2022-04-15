#include "IGameState.h"

namespace falcon {

IGameState::IGameState(Engine* engine):
	_engine(engine),
	_isResourcesLoaded(false) {
}

IGameState::~IGameState() {
}

bool IGameState::isResourcesLoaded() const {
	return _isResourcesLoaded;
}

void IGameState::setResourcesLoaded(bool isLoaded) {
	_isResourcesLoaded = isLoaded;
}

Engine* IGameState::getEngine() const {
	return _engine;
}

}
