#include "IGameState.h"

namespace firefly {

IGameState::IGameState():
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

}
